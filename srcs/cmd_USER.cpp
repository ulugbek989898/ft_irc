/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_USER.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 14:23:05 by uisroilo          #+#    #+#             */
/*   Updated: 2023/04/08 06:09:33 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CommandParse.hpp"

void	CommandParse::parseUsername(std::string userNameMsg, std::vector<Users> Users, int fd) throw(std::runtime_error) {
	pre_username = "";
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
