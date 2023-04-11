/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:08:07 by uisroilo          #+#    #+#             */
/*   Updated: 2023/04/11 16:55:52 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

void	Server::ft_parse(int newUserFd, std::string cmd, std::string msg) throw(std::runtime_error) {
	// memset(&_buf, 0, sizeof(_buf));
	// int nbytes = recv(newUserFd, _buf, sizeof(_buf), 0);
	// if (nbytes <= 0)
	// {
	// 	if (nbytes == 0)
	// 		throw std::runtime_error("Connection closed");
	// 	else
	// 		std::cout << "recieving\n";
	// }
	// else
	// {
	// 	if (cmd == "PASS")
	// 		cmdParse.parsePass(_buf, _password);
	// 	else if (cmd == "NICK")
	// 		cmdParse.parseNick(_buf, _Users, newUserFd);
	// 	else if (cmd == "USER")
	// 		cmdParse.parseUsername(_buf, _Users, newUserFd);
	// 	else if (cmd == "OPER")
	// 		cmdParse.parseOPER(_buf, _Users, newUserFd, _password);
	// }
	if (cmd == "PASS")
			cmdParse.parsePass(msg, _password);
		else if (cmd == "NICK")
			cmdParse.parseNick(msg, _Users, newUserFd);
		else if (cmd == "USER")
			cmdParse.parseUsername(msg, _Users, newUserFd);
		else if (cmd == "OPER")
			cmdParse.parseOPER(_buf, _Users, newUserFd, _password);
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

std::string	Server::getUserBufferWithFd(std::vector<Users> _Users, int fd) {
	std::string	tmp = "";
	for (size_t i = 0; i < _Users.size(); i++)
	{
		if (_Users[i].getUserFd() == fd) {
			return _Users[i].getUserBuffer();
		}
	}
	return tmp;
}

void	Server::setUserBufferWithFd(std::vector<Users> _Users, int fd) {
	for (size_t i = 0; i < _Users.size(); i++)
	{
		if (_Users[i].getUserFd() == fd) {
			// std::cout << "yes sure1 " << _Users[i].getUserBuffer() << std::endl;
			_Users[i].setUserBuffer();
			// std::cout << "yes sure2 " << _Users[i].getUserBuffer() << std::endl;
			break ;
		}
	}
}

std::string		Server::getServername() {
	return _servername;
}

void	Server::checkOrder(int userIndex) throw(std::runtime_error) {
	if (_Users[userIndex].getOrder().size() == 3) {
		for (size_t i = 0; i < _Users[userIndex].getOrder().size(); i++) {
			if (i == 0 && _Users[userIndex].getOrder()[i] != "PASS")
				throw std::runtime_error("Enter first PASS keyword, then NICK and USER");
			if (i == 1 && _Users[userIndex].getOrder()[i] != "NICK")
				throw std::runtime_error("Enter second as NICK keyword, then USER");
			if (i == 2 && _Users[userIndex].getOrder()[i] != "USER")
				throw std::runtime_error("Enter third as USEr keyword");
		}
	}
}