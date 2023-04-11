/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_NOTICE.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:19:16 by uisroilo          #+#    #+#             */
/*   Updated: 2023/04/08 23:05:49 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/NOTICE.hpp"

NOTICE::NOTICE(/* args */)
{
	// servername = SERVER_NAME;
	isUser = false;
	isChannel = false;
}

NOTICE::~NOTICE()
{
}

std::string	NOTICE::getServername() {
	return servername;
}

int		NOTICE::getFdFromUsers(std::string nick, std::vector<Users> _Users) const {
	for (size_t i = 0; i < _Users.size(); i++) {
		if (_Users[i].getUserNick() == nick)
			return _Users[i].getUserFd();
	}
	return 0;
}

void NOTICE::adv_tokenizer(std::string s, char del)
{
	std::stringstream ss(s);
	std::string word;
	while (!ss.eof()) {
		getline(ss, word, del);
		usersChannelsArr.push_back(word);	
	}
}

bool	NOTICE::checkNickExist(std::vector<Users>	_User, std::string nick) {
	for (size_t i = 0; i < _User.size(); i++)
	{
		if (_User[i].getUserNick() == nick) {
			isUser = true;
			return true;
		}
	}
	return false;
}

bool	NOTICE::checkChannelExist(std::vector<Channels> _Channels, std::string channel) {
	for (size_t i = 0; i < _Channels.size(); i++)
	{
		if (_Channels[i].getChannelName() == channel) {
			isChannel = true;
			return true;
		}
	}
	return false;
}

std::vector<int>	NOTICE::getChannelUserFds(std::vector<Channels> _Channels, std::string channel) {
	std::vector<int> tmp;
	for (size_t i = 0; i < _Channels.size(); i++)
	{
		if (_Channels[i].getChannelName() == channel) {
			return _Channels[i].getChannelUserFds();
		}
	}
	return tmp;
}

std::string	NOTICE::getPreNickWithFd(std::vector<Users>	_Users, int fd) {
	for (size_t i = 0; i < _Users.size(); i++) {
			if (_Users[i].getUserFd() == fd) {
				return _Users[i].getUserNick();
			}
		}
	return "";
}

void	NOTICE::parseNoticeMsg(std::string str, std::vector<Users> _Users, std::vector<Channels> _Channels, int newFd, std::string _servername) throw(std::runtime_error) {
	std::stringstream	ss(str);
	std::string			word;
	int					counter = 0;

	servername = _servername;
	privmsgCmdArr.clear();
	msgSend = "";

	while (ss >> word) {
		privmsgCmdArr.push_back(word);
		counter++;
	}
	if (counter == 3)
		msgSend = privmsgCmdArr[2];
	else if (counter > 3) {
		for (size_t i = 2; i < privmsgCmdArr.size(); i++){
			if (i != privmsgCmdArr.size() - 1) {
				msgSend += privmsgCmdArr[i];
				msgSend += " ";
			}
			else {
				msgSend += privmsgCmdArr[i];
			}
		}
	}

	
	if (counter > 2) {
		usersChannelsArr.clear();
		adv_tokenizer(privmsgCmdArr[1], ',');
		for (size_t i = 0; i < usersChannelsArr.size(); i++)
		{
			if (!checkNickExist(_Users, usersChannelsArr[i]) && usersChannelsArr[i][0] != '#') {
				std::string msg = ERR_NOSUCHNICK(getServername(), getPreNickWithFd(_Users, newFd), usersChannelsArr[i]);
				int status = send(newFd, msg.c_str(), msg.length(), 0);
				if (status <= 0)
					throw std::runtime_error("SEND_ERR");
			}
			else if (!checkChannelExist(_Channels, usersChannelsArr[i]) && usersChannelsArr[i][0] == '#') {
				std::string msg = ERR_NOSUCHCHANNEL(getServername(), getPreNickWithFd(_Users, newFd), usersChannelsArr[i]);
				int status = send(newFd, msg.c_str(), msg.length(), 0);
				if (status <= 0)
					throw std::runtime_error("SEND_ERR");
			}
			else {
				if (this->isUser) {
					isUser = false;
					std::string msg = NOTICE_REP(getServername(), getPreNickWithFd(_Users, newFd), usersChannelsArr[i], msgSend);
					int status = send(getFdFromUsers(usersChannelsArr[i], _Users), msg.c_str(), msg.length(), 0);
					if (status <= 0)
						throw std::runtime_error("SEND_ERR");
				}
				else if (this->isChannel) {
					isChannel = false;
					for (size_t j = 0; j < getChannelUserFds(_Channels, usersChannelsArr[i]).size(); j++)
					{
						int	fd = getChannelUserFds(_Channels, usersChannelsArr[i])[j];
						// std::cout << "userFd =" << fd << std::endl;
						std::string msg = NOTICE_REP(getServername(), getPreNickWithFd(_Users, fd), usersChannelsArr[i], msgSend);
						int status = send(fd, msg.c_str(), msg.length(), 0);
						if (status <= 0)
							throw std::runtime_error("SEND_ERR");
					}
					
				}
			}
		}
	}
}
