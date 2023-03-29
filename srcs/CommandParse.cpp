/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandParse.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 08:50:12 by uisroilo          #+#    #+#             */
/*   Updated: 2023/03/29 08:39:57 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CommandParse.hpp"

CommandParse::CommandParse(/* args */)
{
}

CommandParse::~CommandParse()
{
}

void	CommandParse::parse(std::string str) {
	std::cout << "msg: " << str << std::endl;
	
}

void	CommandParse::parsePass(std::string str, std::string password) throw(std::runtime_error) {
	std::stringstream	ss(str);
	std::string			word;
	int					counter = 0;
	
	while (ss >> word) {
		passwordArr.push_back(word);
		counter++;
	}
	
	if (counter != 2) {
		passwordArr.clear();
		throw std::runtime_error(ERR_NEEDMOREPARAMS);
	}

	if (passwordArr[0] == "PASS")
	{
		if (password == passwordArr[1]) {
			std::cout << "password correct" <<std::endl;
		}
		else {
			passwordArr.clear();
			throw std::runtime_error(ERR_PASSWDMISMATCH);
		}
	}
	else {
		passwordArr.clear();
		throw std::runtime_error(CMD_PASS_ERR);
	}
	passwordArr.clear();
}


bool	CommandParse::checkNickExist(std::vector<Users>	_User, std::string nick) {
	for (size_t i = 0; i < _User.size(); i++) {
		if (_User[i].getUserNick() == nick)
			return true;
	}
	return false;
}

bool	CommandParse::checkSymbol(char c) {
	std::string symbols = "-[]`^{}\'";
	for (size_t i = 0; i < symbols.length(); i++) {
		if (c == symbols[i])
			return true;
	}
	return false;
}

bool	CommandParse::checkNickSyntax(std::string nick) {
	if (nick.length() > 10)
		return true;

	for (size_t i = 0; i < nick.length(); i++) {
		if (isdigit(nick[i]) || isalpha(nick[i]) || checkSymbol(nick[i]))
			continue;
		else
			return true;
	}
	return false;
}

std::string	CommandParse::parseNick(std::string nickMsg, std::vector<Users>	_User) throw(std::runtime_error) {
	std::stringstream	ss(nickMsg);
	std::string			word;
	int					counter = 0;
	std::string			ret_nick;
	
	while (ss >> word) {
		nickArr.push_back(word);
		counter++;
	}
	
	if (counter != 2) {
		nickArr.clear();
		throw std::runtime_error(ERR_NEEDMOREPARAMS);
	}

	if (nickArr[0] == "NICK")
	{
		if ((nickArr[1].length() > 10))
		{
			nickArr.clear();
			throw std::runtime_error("try give nick length no more than 10");
		}
		if (checkNickExist(_User, nickArr[1])) {
			nickArr.clear();
			throw std::runtime_error(nickArr[1] + ERR_NICKNAMEINUSE);
		}
		else if (checkNickSyntax(nickArr[1])) {
			nickArr.clear();
			throw std::runtime_error(nickArr[1] + ERR_ERRONEUSNICKNAME);
		}
		else
			std::cout << "You can add this nick to Users class" <<std::endl;
	}
	else {
		nickArr.clear();
		throw std::runtime_error(RAND_ERR);
	}
	ret_nick = nickArr[1];
	nickArr.clear();
	return (ret_nick);
}

std::string	CommandParse::parseUsername(std::string userNameMsg) throw(std::runtime_error) {
	std::stringstream	ss(userNameMsg);
	std::string			word;
	int					counter = 0;
	std::string			ret_user;
	
	while (ss >> word) {
		userNameArr.push_back(word);
		counter++;
	}
	
	if (counter != 5) {
		userNameArr.clear();
		throw std::runtime_error(ERR_NEEDMOREPARAMS);
	}

	if (userNameArr[0] == "USER")
	{
		if (userNameArr[1].length() > 10) {
			userNameArr.clear();
			throw std::runtime_error("try give username length no more than 10");
		}
		else if (checkNickSyntax(userNameArr[1])) {
			userNameArr.clear();
			throw std::runtime_error(userNameArr[1] + ERR_ERRONEUSUSERNAME);
		}
		std::cout << "You can add this user to Users class" <<std::endl;
	}
	else {
		userNameArr.clear();
		throw std::runtime_error(RAND_ERR);
	}
	ret_user = userNameArr[1];
	userNameArr.clear();
	return (ret_user);
}
