/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandParse.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 08:50:12 by uisroilo          #+#    #+#             */
/*   Updated: 2023/04/01 17:10:45 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CommandParse.hpp"

CommandParse::CommandParse(/* args */)
{
	servername = SERVER_NAME;
	isOper = false;
}

std::string	CommandParse::getServerName() {
	return servername;
}

CommandParse::~CommandParse()
{
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


bool	CommandParse::getIsOper() const {
	return isOper;
}
	void	CommandParse::setIsOper(bool val) {
		isOper = val;
	}