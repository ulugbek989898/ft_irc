/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:08:07 by uisroilo          #+#    #+#             */
/*   Updated: 2023/03/29 09:17:14 by uisroilo         ###   ########.fr       */
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
			pre_nick = cmdParse.parseNick(_buf, _Users);
		else if (cmd == "USER")
			pre_username = cmdParse.parseUsername(_buf);
	}
}
