/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_NICK.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 14:26:07 by uisroilo          #+#    #+#             */
/*   Updated: 2023/04/01 14:26:19 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CommandParse.hpp"

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
