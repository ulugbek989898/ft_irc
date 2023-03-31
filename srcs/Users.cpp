/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Users.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrangwan <rrangwan@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:10:46 by uisroilo          #+#    #+#             */
/*   Updated: 2023/03/31 19:10:15 by rrangwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Users.hpp"

Users::Users(int fd, std::string pre_nick, std::string pre_username):user_fd(fd), user_nick(pre_nick), username(pre_username)
{
	std::cout << "new user fd = " << user_fd << "; username =" << username << std::endl;
	this->isOPER = false;
}

Users::~Users()
{}

std::string	Users::getUserNick(void) const {
	return user_nick;
}

int			Users::getUserFd(void) const {
	return user_fd;
}
std::string	Users::getUserName(void) const {
	return username;
}


bool	Users::getUserOPER(void) const {
	return isOPER;
}


void	Users::setNick(std::string nick) {
	user_nick = nick;
}

void	Users::setOPER(bool val) {
	isOPER = val;
}
