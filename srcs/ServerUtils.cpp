/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrangwan <rrangwan@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:08:07 by uisroilo          #+#    #+#             */
/*   Updated: 2023/03/31 19:41:49 by rrangwan         ###   ########.fr       */
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
	return NULL;
}
