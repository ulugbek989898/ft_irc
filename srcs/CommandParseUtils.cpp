/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandParseUtils.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 12:16:15 by uisroilo          #+#    #+#             */
/*   Updated: 2023/04/12 06:47:52 by uisroilo         ###   ########.fr       */
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

std::string	CommandParse::getPrePassword() {
	return pre_password;
}

std::string	CommandParse::getCmd() {
	return _cmd;
}

JOIN	CommandParse::getJOIN() {
	return cmdJOIN;
}

void	CommandParse::parse(std::string str, std::vector<Users>	_Users, std::vector<Channels> _Channels, int newFd, std::string _servername) throw(std::runtime_error) {
	std::stringstream	ss(str);
	std::string			word;
	int					counter = 0;

	servername = _servername;
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
			recievingMsgArr.clear();
			cmdKILL.parseKill(str, _Users, newFd);
			_cmd = "KILL";
		}
		else if (counter && recievingMsgArr[0] == "QUIT") {
			recievingMsgArr.clear();
			cmdQUIT.parseQuit(str, _Users, newFd, _servername);
			_cmd = "QUIT";
		}
		else if (counter && recievingMsgArr[0] == "SQUIT") {
			recievingMsgArr.clear();
			cmdSQUIT.parseSquit(str, _Users, newFd, _servername);
			_cmd = "SQUIT";
		}
		else if (counter && recievingMsgArr[0] == "JOIN") {
			recievingMsgArr.clear();
			cmdJOIN.parseJoin(str, _Users, newFd, _servername);
			_cmd = "JOIN";
		}
		else if (counter && recievingMsgArr[0] == "PRIVMSG") {
			recievingMsgArr.clear();
			cmdPRIVMSG.parsePrivmsg(str, _Users, _Channels, newFd, _servername);
			_cmd = "PRIVMSG";
		}
		else if (counter && recievingMsgArr[0] == "NOTICE") {
			recievingMsgArr.clear();
			cmdNOTICE.parseNoticeMsg(str, _Users, _Channels, newFd, _servername);
			_cmd = "NOTICE";
		}
		else {
			recievingMsgArr.clear();
			_cmd = "";
			// std::string msg = ERR_UNKNOWNCOMMAND(getServerName(), recievingMsgArr[0]);
			// int status = send(newFd, msg.c_str(), msg.length(), 0);
			// if (status <= 0)
			// 	throw std::runtime_error("SEND_ERR");
		}
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
