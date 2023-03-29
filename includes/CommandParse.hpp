/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandParse.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 08:30:21 by uisroilo          #+#    #+#             */
/*   Updated: 2023/03/29 07:45:29 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDPARSE_HPP
# define COMMANDPARSE_HPP

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include "Users.hpp"
// #include "Server.hpp" // Include the Server header file

# define ERR_NEEDMOREPARAMS "need more params"
# define ERR_PASSWDMISMATCH ":Password incorrect"
# define CMD_PASS_ERR "Typing PASS invalid"
# define ERR_NICKNAMEINUSE " :Nickname is already in use"
# define ERR_ERRONEUSNICKNAME " :Erroneus nickname"
# define RAND_ERR "As second input it must 'NICK nickname'"
# define ERR_ERRONEUSUSERNAME " :Erroneus nickname"

class Users;

class CommandParse
{
private:
	std::string	_cmd;
	std::string	_parameters;
	std::vector<std::string>	passwordArr;
	std::vector<std::string>	nickArr;
	std::vector<std::string>	userNameArr;
public:
	CommandParse();
	~CommandParse();
	void	parse(std::string recieved_msg);
	void	parsePass(std::string passMsg, std::string password) throw(std::runtime_error);

	std::string	parseNick(std::string nickMsg, std::vector<Users> Users) throw(std::runtime_error);
	bool		checkNickExist(std::vector<Users>	_User, std::string nick);
	bool		checkNickSyntax(std::string nick);
	bool		checkSymbol(char c);

	std::string	parseUsername(std::string _buf) throw(std::runtime_error);
};

#endif