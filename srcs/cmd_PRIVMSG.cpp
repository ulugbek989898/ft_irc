/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_PRIVMSG.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:26:14 by uisroilo          #+#    #+#             */
/*   Updated: 2023/04/06 08:04:43 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PRIVMSG.hpp"

PRIVMSG::PRIVMSG(/* args */)
{
	servername = SERVER_NAME;
}

PRIVMSG::~PRIVMSG()
{
}

std::string	PRIVMSG::getServername() {
	return servername;
}

void PRIVMSG::adv_tokenizer(std::string s, char del)
{
	std::stringstream ss(s);
	std::string word;
	while (!ss.eof()) {
		getline(ss, word, del);
		usersChannelsArr.push_back(word);		
	}
}

bool	PRIVMSG::checkNickExist(std::vector<Users>	_User, std::string nick) {
	for (size_t i = 0; i < _User.size(); i++)
	{
		if (_User[i].getUserName() == nick)
			return true;
	}
	printf("hello\n");
	return false;
}

std::string	PRIVMSG::getPreNickWithFd(std::vector<Users>	_Users, int fd) {
	for (size_t i = 0; i < _Users.size(); i++) {
			if (_Users[i].getUserFd() == fd) {
				return _Users[i].getUserNick();
			}
		}
	return "";
}

void	PRIVMSG::parsePrivmsg(std::string str, std::vector<Users> _Users, int newFd) throw(std::runtime_error) {
	printf("res = %s\n", str.c_str());
	std::stringstream	ss(str);
	std::string			word;
	int					counter = 0;

	privmsgCmdArr.clear();

	while (ss >> word) {
		privmsgCmdArr.push_back(word);
		counter++;
	}
	
	if (counter > 2) {
		usersChannelsArr.clear();
		adv_tokenizer(privmsgCmdArr[1], ',');
		for (size_t i = 0; i < usersChannelsArr.size(); i++)
		{
			if (!checkNickExist(_Users, usersChannelsArr[i]))
				throw std::runtime_error(ERR_NOSUCHNICK(getServername(), getPreNickWithFd(_Users, newFd), usersChannelsArr[i]));
			//also checkChannelExist()
			// else if ()
		}
		
	}
}