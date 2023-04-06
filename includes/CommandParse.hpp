/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandParse.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 08:30:21 by uisroilo          #+#    #+#             */
/*   Updated: 2023/04/06 14:41:05 by uisroilo         ###   ########.fr       */
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
#include "KILL.hpp"
#include "QUIT.hpp"
#include "SQUIT.hpp"
#include "Reply.hpp"
#include "JOIN.hpp"
#include "PRIVMSG.hpp"
#include "Channels.hpp"


class Users;

class CommandParse
{
private:
	std::string	_cmd;
	std::string	_parameters;
	std::vector<std::string>	passwordArr;
	std::vector<std::string>	passwordArrTemp;
	std::vector<std::string>	nickArr;
	std::vector<std::string>	userNameArr;
	std::vector<std::string>	recievingMsgArr;

	std::string					servername;
	std::string					pre_nick;
	std::string					pre_username;

	std::string					_password;
	bool						isOper;
	KILL						cmdKILL;
	QUIT						cmdQUIT;
	SQUIT						cmdSQUIT;
	JOIN						cmdJOIN;
	PRIVMSG						cmdPRIVMSG;
	
public:
	CommandParse();
	~CommandParse();
	std::string		getPreNick();
	std::string		getPreNickWithFd(std::vector<Users>	_Users, int fd);
	bool			getIsOperWithFd(std::vector<Users>	_Users, int fd);
	std::string		getPreUsername();
	std::string		getPreUsernameWithFd(std::vector<Users>	_Users, int fd);
	std::string		getServerName();
	std::string		getCmd();
	void		parse(std::string recieved_msg, std::vector<Users>	_User, std::vector<Channels> _Channels, int newFd) throw(std::runtime_error);
	void		parsePass(std::string passMsg, std::string password) throw(std::runtime_error);
	void		parseNick(std::string nickMsg, std::vector<Users> Users, int fd) throw(std::runtime_error);
	void		parseUsername(std::string _buf, std::vector<Users> Users, int fd) throw(std::runtime_error);

	void		parseOPER(std::string _buf, std::vector<Users> Users, int fd, std::string password) throw(std::runtime_error);
	bool		checkNickExist(std::vector<Users>	_User, std::string nick, int fd);
	bool		checkNickSyntax(std::string nick);
	bool		checkSymbol(char c);
	bool		getIsOper() const;
	void		setIsOper(bool val);
	int			getFdFromUsers(std::string nick, std::vector<Users>	_User) const;
	std::string	getNickWithIndex(int index) const;
	JOIN		getJOIN();

};

#endif
