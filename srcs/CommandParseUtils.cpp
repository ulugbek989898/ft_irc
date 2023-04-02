/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandParseUtils.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 12:16:15 by uisroilo          #+#    #+#             */
/*   Updated: 2023/04/02 15:02:23 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CommandParse.hpp"

std::string	CommandParse::getPreNick() {
	return pre_nick;
}

std::string	CommandParse::getPreNickWithFd(std::vector<Users>	_Users, int fd) {
	for (size_t i = 0; i < _Users.size(); i++) {
			if (_Users[i].getUserFd() == fd) {
				return _Users[i].getUserNick();
			}
		}
	return "";
}

std::string	CommandParse::getPreUsernameWithFd(std::vector<Users>	_Users, int fd) {
	for (size_t i = 0; i < _Users.size(); i++) {
			if (_Users[i].getUserFd() == fd) {
				return _Users[i].getUserName();
			}
		}
	return "";
}

std::string	CommandParse::getPreUsername() {
	return pre_username;
}

std::string	CommandParse::getCmd() {
	return _cmd;
}

void	CommandParse::parse(std::string str, std::vector<Users>	_Users, int newFd) throw(std::runtime_error) {
	std::stringstream	ss(str);
	std::string			word;
	int					counter = 0;

	recievingMsgArr.clear();
	while (ss >> word) {
		recievingMsgArr.push_back(word);
		counter++;
	}
	try
	{
		if (counter && recievingMsgArr[0] == "NICK")
		{
			recievingMsgArr.clear();
			parseNick(str, _Users, newFd);
			_cmd = "NICK";
		}
		else if (counter && recievingMsgArr[0] == "USER") {
			recievingMsgArr.clear();
			parseUsername(str, _Users, newFd);
			_cmd = "USER";
		}
		else if (counter && recievingMsgArr[0] == "OPER") {
			recievingMsgArr.clear();
			parseOPER(str, _Users, newFd, this->_password);
			_cmd = "OPER";
		}
		else if (counter && recievingMsgArr[0] == "KILL") {
			cmdKILL.parseKill(str, _Users, newFd);
			_cmd = "KILL";
		}
		else if (counter && recievingMsgArr[0] == "QUIT") {
			cmdQUIT.parseQuit(str, _Users, newFd);
			_cmd = "QUIT";
		}
		else
			_cmd = "";
	}
	catch(const std::exception& e)
	{
		_cmd = "";
		std::string msg = e.what();
		int status = send(newFd, msg.c_str(), msg.length(), 0);
		if (status <= 0)
			throw std::runtime_error("SEND_ERR");
	}
}
