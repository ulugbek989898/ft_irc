/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KILL.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 21:46:48 by uisroilo          #+#    #+#             */
/*   Updated: 2023/04/02 14:14:23 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/KILL.hpp"

KILL::KILL(/* args */)
{
	servername = SERVER_NAME;
}

std::string		KILL::getServername() {
	return servername;
}

KILL::~KILL()
{
}

std::string	KILL::getPreNickWithFd(std::vector<Users>	_Users, int fd) {
	for (size_t i = 0; i < _Users.size(); i++) {
			if (_Users[i].getUserFd() == fd) {
				return _Users[i].getUserNick();
			}
		}
	return "";
}

bool	KILL::getIsOperWithFd(std::vector<Users>	_Users, int fd) {
	for (size_t i = 0; i < _Users.size(); i++) {
			if (_Users[i].getUserFd() == fd) {
				return _Users[i].getUserOPER();
			}
		}
	return false;
}

bool	KILL::checkNickExist(std::vector<Users>	_Users, std::string killedNick, int fd) {
	for (size_t i = 0; i < _Users.size(); i++) {
			if (_Users[i].getUserNick() == killedNick && _Users[i].getUserFd() != fd) {
				return true;
			}
		}
	return false;
}

void	KILL::parseKill(std::string str, std::vector<Users>	_User, int fd) throw(std::runtime_error) {
	std::stringstream	ss(str);
	std::string			word;
	int					counter = 0;

	killCmdArr.clear();

	while (ss >> word) {
		killCmdArr.push_back(word);
		counter++;
	}
	if (counter < 3) {
		killCmdArr.clear();
		throw std::runtime_error(ERR_NEEDMOREPARAMS(getServername(), getPreNickWithFd(_User, fd), "KILL"));
	}
	else if (!checkNickExist(_User, killCmdArr[1], fd)) {
		killCmdArr.clear();
		throw std::runtime_error(ERR_ERRONEUSNICKNAME(getServername(), getPreNickWithFd(_User, fd)));
	}
	else if (getIsOperWithFd(_User, fd) != true) {
		killCmdArr.clear();
		throw std::runtime_error(ERR_NOPRIVILEGES(getServername(), getPreNickWithFd(_User, fd)));
	}
	// send to everyone comment from operator why he kill user
	std::string tmp;
	for (int j = 2; j < counter; j++) {
		if (j != counter - 1)
			tmp += killCmdArr[j] + " ";
		else
			tmp += killCmdArr[j];
	}
	memset(&buffer, 0, sizeof(buffer));
	tmp = RPL_KILL(getServername(), killCmdArr[1], tmp);
	tmp.copy(buffer, sizeof(buffer));
	
	for (size_t i = 0; i < _User.size(); i++) {
		if (send(_User[i].getUserFd(), buffer, tmp.length() , 0) == -1) {
			perror("send");
		}
	}
}
