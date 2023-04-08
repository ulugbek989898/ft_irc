/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:08:07 by uisroilo          #+#    #+#             */
/*   Updated: 2023/04/08 06:09:19 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

void	Server::ft_parse(int newUserFd, std::string cmd) throw(std::runtime_error) {
	memset(&_buf, 0, sizeof(_buf));
	int nbytes = recv(newUserFd, _buf, sizeof(_buf), 0);
	if (nbytes <= 0)
	{
		if (nbytes == 0)
			throw std::runtime_error("Connection closed");
		else
			perror("reciving:");
	}
	else
	{
		if (cmd == "PASS")
			cmdParse.parsePass(_buf, _password);
		else if (cmd == "NICK")
			cmdParse.parseNick(_buf, _Users, newUserFd);
		else if (cmd == "USER")
			cmdParse.parseUsername(_buf, _Users, newUserFd);
		else if (cmd == "OPER")
			cmdParse.parseOPER(_buf, _Users, newUserFd, _password);
	}
}

std::string		Server::getNickFromUsers(int fd) const {
	for (size_t i = 0; i < _Users.size(); i++) {
		if (_Users[i].getUserFd() == fd)
			return _Users[i].getUserNick();
	}
	return "";
}

void	Server::setIsOperWithFd(bool val, int fd) {
	for (size_t i = 0; i < _Users.size(); i++)
	{
		if (fd == _Users[i].getUserFd())
			_Users[i].setOPER(val);
	}
}

bool	Server::checkUserInChannel(std::string chan, int fd) {
	for (size_t i = 0; i < this->_Users.size(); i++) {
		if (this->_Users[i].getUserFd() == fd) {
			for (size_t j = 0; j < this->_Users[i].getChannelList().size(); j++) {
				if (this->_Users[i].getChannelList()[j] == chan)
					return true;
			}
		}
	}
	return false;
}

bool	Server::checkChannelExistInChannelList(std::string chan) {
	for (size_t i = 0; i < this->_Channels.size(); i++) {
		if (this->_Channels[i].getChannelName() == chan) {
			std::cout << "str="<<chan<<"," << this->_Channels[i].getChannelName() << std::endl;
			return true;
		}
	}
	return false;
}