/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Printing.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:21:31 by uisroilo          #+#    #+#             */
/*   Updated: 2023/04/01 16:32:40 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

void	Server::ft_print_users() const {
	std::cout << GREEN << "/* ******************************************** */\n";
	std::cout << "/* Fds           Nick        Username   Operator*/\n";
	for (size_t i = 0; i < _Users.size(); i++) {
		std::cout << YELLOW << "/* ";
		std::cout << std::left << std::setfill(' ') << std::setw(14);
		std::cout << _Users[i].getUserFd();
		std::cout << std::left << std::setfill(' ') << std::setw(12);
		std::cout << _Users[i].getUserNick();
		std::cout << std::left << std::setfill(' ') << std::setw(11);
		std::cout << _Users[i].getUserName();
		std::cout << std::left << std::setfill(' ') << std::setw(11);
		if (_Users[i].getUserOPER())
			std::cout << "true";
		else
			std::cout << "false";
		std::cout << "*/" << std::endl;
	}
	std::cout << GREEN << "/* ******************************************** */\n";
}

void	Server::ft_show_auth_usage(int fd) throw(std::runtime_error) {
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

	void	Server::showGeneralGuide(int fd) throw(std::runtime_error) {
		int			status;
	std::string	msg;
	msg += "001 " + cmdParse.getPreNick() + " /* ********************************************************************** */\r\n";
	msg += "001 " + cmdParse.getPreNick() + " /* ************************** General Guide ***************************** */\r\n";
	msg += "001 " + cmdParse.getPreNick() + " /*        Commands: USER, NICK, OPER, KILL, SQUIT, QUIT, JOIN, PRIVMSG, NOTICE  */\r\n";
	msg += "001 " + cmdParse.getPreNick() + " /* ********************************************************************** */\r\n";
	msg += "001 " + cmdParse.getPreNick() + " /* setting new userName: 'USER <newUserName> 0 * <realName>' */\r\n";
	msg += "001 " + cmdParse.getPreNick() + " /* setting new nickName: 'NICK <nickname>' */\r\n";
	msg += "001 " + cmdParse.getPreNick() + " /* getting operator privileges to normal user: 'OPER <nickname> <pass>' */\r\n";
	msg += "001 " + cmdParse.getPreNick() + " /* close the connection between a given client and the server: 'KILL <nickname> <comment>' */\r\n";
	msg += "001 " + cmdParse.getPreNick() + " /* disconnects a server from the network: 'SQUIT <server> :<comment>' */\r\n";
	msg += "001 " + cmdParse.getPreNick() + " /* terminate a client’s connection to the server: 'QUIT' */\r\n";
	msg += "001 " + cmdParse.getPreNick() + " /* creating or joining existing channel: 'JOIN #<channel>' */\r\n";
	msg += "001 " + cmdParse.getPreNick() + " /* send private messages to user or to channel: 'PRIVMSG <target>: <message>' */\r\n";
	msg += "001 " + cmdParse.getPreNick() + " /* send private messages to user or to channel: 'NOTICE <target> :<message>' */\r\n";
	msg += "001 " + cmdParse.getPreNick() + " /* ********************************************************************** */\r\n";
	status = send(fd, msg.c_str(), msg.length(), 0);
	checkStatusAndThrow(status, SEND_ERR);
}
