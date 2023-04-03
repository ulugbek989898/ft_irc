/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_SQUIT.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 16:22:47 by uisroilo          #+#    #+#             */
/*   Updated: 2023/04/03 06:35:28 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/SQUIT.hpp"

SQUIT::SQUIT(/* args */)
{
	servername = SERVER_NAME;
}

SQUIT::~SQUIT()
{
}

std::string	SQUIT::getServerName() {
	return servername;
}

std::string	SQUIT::getPreNickWithFd(std::vector<Users>	_Users, int fd) {
	for (size_t i = 0; i < _Users.size(); i++) {
			if (_Users[i].getUserFd() == fd) {
				return _Users[i].getUserNick();
			}
		}
	return "";
}

bool	SQUIT::getIsOperWithFd(std::vector<Users>	_Users, int fd) {
	for (size_t i = 0; i < _Users.size(); i++) {
			if (_Users[i].getUserFd() == fd) {
				return _Users[i].getUserOPER();
			}
		}
	return false;
}

void	SQUIT::parseSquit(std::string str, std::vector<Users>	_User, int fd) throw(std::runtime_error) {
	std::stringstream	ss(str);
	std::string			word;
	int					counter = 0;

	squitCmdArr.clear();

	while (ss >> word) {
		squitCmdArr.push_back(word);
		counter++;
	}
	if (counter < 3) {
		squitCmdArr.clear();
		throw std::runtime_error(ERR_NEEDMOREPARAMS(getServerName(), getPreNickWithFd(_User, fd), "SQUIT"));
	}
	else if (getServerName() != squitCmdArr[1]) {
		squitCmdArr.clear();
		throw std::runtime_error(ERR_NOSUCHSERVER(squitCmdArr[1], getPreNickWithFd(_User, fd)));
	}
	else if (getIsOperWithFd(_User, fd) != true) {
		squitCmdArr.clear();
		throw std::runtime_error(ERR_NOPRIVILEGES(getServerName(), getPreNickWithFd(_User, fd)));
	}

	std::string tmp;
	for (int j = 2; j < counter; j++) {
		if (j != counter - 1)
			tmp += squitCmdArr[j] + " ";
		else
			tmp += squitCmdArr[j];
	}
	memset(&buffer, 0, sizeof(buffer));
	tmp = RPL_SQUIT(getServerName(), squitCmdArr[1], tmp);
	tmp.copy(buffer, sizeof(buffer));
	
	for (size_t i = 0; i < _User.size(); i++) {
		if (send(_User[i].getUserFd(), buffer, tmp.length() , 0) == -1) {
			perror("send");
		}
	}
}