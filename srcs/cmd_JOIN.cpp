/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_JOIN.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 09:09:05 by uisroilo          #+#    #+#             */
/*   Updated: 2023/04/08 07:10:09 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/JOIN.hpp"

JOIN::~JOIN()
{
}

JOIN::JOIN(/* args */)
{
	// servername = SERVER_NAME;
}

std::string	JOIN::getPreNickWithFd(std::vector<Users>	_Users, int fd) {
	for (size_t i = 0; i < _Users.size(); i++) {
			if (_Users[i].getUserFd() == fd) {
				return _Users[i].getUserNick();
			}
		}
	return "";
}

std::string		JOIN::getServername() {
	return servername;
}

void JOIN::adv_tokenizer(std::string s, char del, std::vector<Users>	_User, int fd)
{
	std::stringstream ss(s);
	std::string word;
	ChannelsArr.clear();
	while (!ss.eof()) {
		getline(ss, word, del);
		if (word[0] == '#') {
			ChannelsArr.push_back(word);
			std::string msg = REP_CHAN_SUCCESS(getServername(), getPreNickWithFd(_User, fd), word);
			int status = send(fd, msg.c_str(), msg.length(), 0);
			if (status <= 0)
				throw std::runtime_error("SEND_ERR");
		}
		else {
			std::string msg = ERR_BADCHANMASK(getServername(), getPreNickWithFd(_User, fd), word);
			int status = send(fd, msg.c_str(), msg.length(), 0);
			if (status <= 0)
				throw std::runtime_error("SEND_ERR");
		}
	}
}

std::vector<std::string>	JOIN::getChannelsArr() {
	return ChannelsArr;
}

void	JOIN::parseJoin(std::string str, std::vector<Users>	_User, int fd, std::string _servername) throw(std::runtime_error) {
	(void) _User;
	(void) fd;
	servername = _servername;
	std::stringstream	ss(str);
	std::string			word;
	int					counter = 0;

	joinCmdArr.clear();

	while (ss >> word) {
		joinCmdArr.push_back(word);
		counter++;
	}
	adv_tokenizer(joinCmdArr[1], ',', _User, fd);
	
}