/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Printing.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:21:31 by uisroilo          #+#    #+#             */
/*   Updated: 2023/03/28 16:48:21 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

void	Server::ft_print_users() const {
	std::cout << GREEN << "/* ************************************ */\n";
	std::cout << "/* Fds           Nick        Username   */\n";
	for (size_t i = 0; i < _Users.size(); i++) {
		std::cout << YELLOW << "/* ";
		std::cout << std::left << std::setfill(' ') << std::setw(14);
		std::cout << _Users[i].getUserFd();
		std::cout << std::left << std::setfill(' ') << std::setw(12);
		std::cout << _Users[i].getUserNick();
		std::cout << std::left << std::setfill(' ') << std::setw(11);
		std::cout << _Users[i].getUserName();
		std::cout << "*/" << std::endl;
	}
	std::cout << GREEN << "/* ************************************ */\n";
}

void	Server::ft_show_usage(int fd) throw(std::runtime_error) {
	(void)fd;
	int			status;
	std::string	msg = BLUE;
	msg += "/* ******************************************************************************************** */\r\n";
	msg += "/* write PASS cmd and password, only 2 arguments. ex-> 'PASS passwordHere'                      */\r\n";
	msg += "/* write NICK cmd and nickname, only 2 arguments. ex-> 'NICK nickhere'                          */\r\n";
	msg += "/* write USER cmd and nickname other 3 params, only 5 arguments. ex-> 'USER usernameHere 3 4 5' */\r\n";
	msg += "/* ******************************************************************************************** */\r\n";
	status = send(fd, msg.c_str(), msg.length(), 0);
	checkStatusAndThrow(status, SEND_ERR);
}