/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandParse.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 08:30:21 by uisroilo          #+#    #+#             */
/*   Updated: 2023/03/31 17:10:11 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDPARSE_HPP
# define COMMANDPARSE_HPP

#include <sys/socket.h>
#include <string>
#include <iostream>
#include<unistd.h>
#include <sstream>
#include <vector>
#include <stdexcept>
#include "Users.hpp"
// #include "Server.hpp" // Include the Server header file
#define SERVER_NAME "localhost"

#define ERR_NEEDMOREPARAMS(servername, client, command) \
(":" + servername + " 461 * " + client + " " + command + " :Not enough parameters\n")

#define ERR_ALREADYREGISTERED(servername, nickname) \
(":" + servername + " 461 * " + nickname + " " + " :You may not reregister\n")

#define ERR_NICKNAMEINUSE(servername, nickname) \
(":" + servername + " 433 " + nickname + " " + " :Nickname is already in use\r\n")

#define ERR_ERRONEUSNICKNAME(servername, nickname) \
(":" + servername + " 432 " + nickname + " " + " :Erroneus nickname\r\n")


# define ERR_PASSWDMISMATCH ":Password incorrect\r\n"
# define CMD_PASS_ERR "Typing PASS invalid or check your password\r\n"
// # define ERR_NICKNAMEINUSE " :Nickname is already in use\r\n"
# define RAND_ERR "As second input it must 'NICK nickname\r\n'"
# define ERR_ERRONEUSUSERNAME "Erroneus nickname\r\n"

#define ERR_NONICKNAMEGIVEN(servername, nickname) \
(":" + servername + " 431 " + nickname + " :No nickname given\n")

class Users;

class CommandParse
{
private:
	std::string	_cmd;
	std::string	_parameters;
	std::vector<std::string>	passwordArr;
	std::vector<std::string>	nickArr;
	std::vector<std::string>	userNameArr;
	std::vector<std::string>	recievingMsgArr;

	std::string					servername;
	std::string					pre_nick;
	std::string					pre_username;
	// Quit						quiting;
public:
	CommandParse();
	~CommandParse();
	std::string		getPreNick();
	std::string		getPreNickWithFd(std::vector<Users>	_Users, int fd);
	std::string		getPreUsername();
	std::string		getPreUsernameWithFd(std::vector<Users>	_Users, int fd);
	std::string		getServerName();
	std::string		getCmd();
	void		parse(std::string recieved_msg, std::vector<Users>	_User, int newFd) throw(std::runtime_error);
	void		parsePass(std::string passMsg, std::string password) throw(std::runtime_error);
	void		parseNick(std::string nickMsg, std::vector<Users> Users, int fd) throw(std::runtime_error);
	void		parseUsername(std::string _buf, std::vector<Users> Users, int fd) throw(std::runtime_error);

	bool		checkNickExist(std::vector<Users>	_User, std::string nick, int fd);
	bool		checkNickSyntax(std::string nick);
	bool		checkSymbol(char c);

};

#endif