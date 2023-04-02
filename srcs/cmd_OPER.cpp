/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_OPER.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 14:21:13 by uisroilo          #+#    #+#             */
/*   Updated: 2023/04/01 21:33:56 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CommandParse.hpp"
void	CommandParse::parseOPER(std::string str, std::vector<Users>	_User, int fd, std::string password) throw(std::runtime_error) {
	std::stringstream	ss(str);
	std::string			word;
	int					counter = 0;

	passwordArrTemp.clear();

	while (ss >> word) {
		passwordArrTemp.push_back(word);
		counter++;
	}
	if (counter < 3) {
		passwordArrTemp.clear();
		throw std::runtime_error(ERR_NEEDMOREPARAMS(getServerName(), getPreUsernameWithFd(_User, fd), "OPER"));
	}
	else if (passwordArrTemp[0] == "OPER")
	{
		if (getPreNickWithFd(_User, fd) != passwordArrTemp[1]) {
			passwordArrTemp.clear();
			throw std::runtime_error(ERR_ERRONEUSNICKNAME(getServerName(), getPreNickWithFd(_User, fd)));
		}
		else if (password != passwordArrTemp[2]) {
			passwordArrTemp.clear();
			throw std::runtime_error(ERR_NOOPERHOST(getServerName(), getPreNickWithFd(_User, fd)));
		}
	}
	else {
		passwordArrTemp.clear();
		throw std::runtime_error(ERR_NOOPERHOST(getServerName(), getPreNickWithFd(_User, fd)));
	}


	passwordArrTemp.clear();

	std::vector<Users>::iterator it = _User.begin();
	while (it != _User.end())
	{
		if (it->getUserFd() == fd) {
			// it->setOPER(true);
			this->setIsOper(true);
			std::string msg = RPL_YOUREOPER(getServerName(), it->getUserNick());
			int status = send(fd, msg.c_str(), msg.length(), 0);
			if (status <= 0)
				throw std::runtime_error("SEND_ERR");
		}
		++it;
	}
}
