/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandParse.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrangwan <rrangwan@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 08:50:12 by uisroilo          #+#    #+#             */
/*   Updated: 2023/03/31 19:58:44 by rrangwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CommandParse.hpp"

CommandParse::CommandParse(/* args */)
{
	servername = SERVER_NAME;
}

std::string	CommandParse::getServerName() {
	return servername;
}

CommandParse::~CommandParse()
{
}

void	CommandParse::parsePass(std::string str, std::string password) throw(std::runtime_error) {
	std::stringstream	ss(str);
	std::string			word;
	int					counter = 0;

	this->_password = password;

	while (ss >> word) {
		passwordArr.push_back(word);
		counter++;
	}
	if (counter != 2) {
		passwordArr.clear();
		throw std::runtime_error("Not enough parameters");
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


bool	CommandParse::checkNickExist(std::vector<Users>	_User, std::string nick, int fd) {
	if (fd == 0) {
		for (size_t i = 0; i < _User.size(); i++) {
			if (_User[i].getUserNick() == nick)
				return true;
		}
	}
	else {
		for (size_t i = 0; i < _User.size(); i++) {
			if (_User[i].getUserFd() == fd)
				return true;
		}
	}
	return false;
}

bool	CommandParse::checkSymbol(char c) {
	std::string symbols = "-[]`^{}\\";
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

void	CommandParse::parseNick(std::string nickMsg, std::vector<Users>	_User, int fd) throw(std::runtime_error) {
	std::stringstream	ss(nickMsg);
	std::string			word;
	int					counter = 0;
	(void)fd;

	while (ss >> word && counter != 2) {
		nickArr.push_back(word);
		counter++;
	}
	if (counter != 2) {
		nickArr.clear();
		throw std::runtime_error("ERR_NEEDMOREPARAMS\n");
	}
	if (nickArr[0] == "NICK")
	{
		if ((nickArr[1].length() > 10))
		{
			nickArr.clear();
			throw std::runtime_error("try give nick length no more than 10");
		}
		if (checkNickExist(_User, nickArr[1], 0)) {
			nickArr.clear();
			throw std::runtime_error(nickArr[1] + ERR_NICKNAMEINUSE(getServerName(), getPreNickWithFd(_User, fd)));
		}
		else if (nickArr[1] == ":"){
			nickArr.clear();
			throw std::runtime_error(ERR_NONICKNAMEGIVEN(getServerName(), getPreNickWithFd(_User, fd)));
		}
		else if (checkNickSyntax(nickArr[1])) {
			nickArr.clear();
			throw std::runtime_error(ERR_ERRONEUSNICKNAME(getServerName(), getPreNickWithFd(_User, fd)));
		}
	}
	else {
		nickArr.clear();
		throw std::runtime_error(RAND_ERR);
	}
	pre_nick = nickArr[1];
	nickArr.clear();
}

void	CommandParse::parseUsername(std::string userNameMsg, std::vector<Users> Users, int fd) throw(std::runtime_error) {
	std::stringstream	ss(userNameMsg);
	std::string			word;
	int					counter = 0;
	while (ss >> word) {
		userNameArr.push_back(word);
		counter++;
	}

	if (counter != 5) {
		userNameArr.clear();
		std::string tmpUsername = getPreUsernameWithFd(Users, fd);
		if (tmpUsername.empty())
			throw std::runtime_error(ERR_NEEDMOREPARAMS(getServerName(), "empty", "USER"));
		else
			throw std::runtime_error(ERR_NEEDMOREPARAMS(getServerName(), getPreUsernameWithFd(Users, fd), "USER"));
	}

	if (userNameArr[0] == "USER")
	{
		std::string tmpUsername = getPreUsernameWithFd(Users, fd);
		if (!tmpUsername.empty()) {
			userNameArr.clear();
			throw std::runtime_error(ERR_ALREADYREGISTERED(getServerName(), pre_username));
		}
		if (userNameArr[1].length() > 10) {
			userNameArr.clear();
			throw std::runtime_error("try give username length no more than 10");
		}
		else if (checkNickSyntax(userNameArr[1])) {
			userNameArr.clear();
			throw std::runtime_error(userNameArr[1] + ERR_ERRONEUSUSERNAME);
		}
	}
	else {
		userNameArr.clear();
		throw std::runtime_error(RAND_ERR);
	}
	pre_username = userNameArr[1];
	userNameArr.clear();
}

void	CommandParse::parseOPER(std::string str, std::vector<Users>	_User, int fd, std::string password) throw(std::runtime_error) {
	std::stringstream	ss(str);
	std::string			word;
	int					counter = 0;

	passwordArrTemp.clear();

	while (ss >> word) {
		passwordArrTemp.push_back(word);
		counter++;
	}
	if (counter != 3) {
		passwordArrTemp.clear();
		throw std::runtime_error("Not enough parameters");
	}
//std::cout << "password arra" <<passwordArrTemp[0] << std::endl;
	if (passwordArrTemp[0] == "OPER")
	{
		if (password == passwordArrTemp[2]) {
			std::cout << "password to make oper correct" <<std::endl;
		}
		else {
			passwordArrTemp.clear();
			throw std::runtime_error(ERR_PASSWDMISMATCH);
		}
	}
	else {
		passwordArrTemp.clear();
		throw std::runtime_error(CMD_PASS_ERR);
	}


	passwordArrTemp.clear();

	std::vector<Users>::iterator it = _User.begin();
	while (it != _User.end())
	{
		if (it->getUserFd() == fd) {
			it->setOPER(true);
			std::cout << it->getUserNick()<<" made operator" <<std::endl;
			break ;
		}
		++it;
	}



}
