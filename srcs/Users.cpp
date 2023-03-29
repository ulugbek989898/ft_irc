/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Users.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:10:46 by uisroilo          #+#    #+#             */
/*   Updated: 2023/03/28 18:04:06 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Users.hpp"

Users::Users(int fd, std::string pre_nick, std::string pre_username):user_fd(fd), user_nick(pre_nick), username(pre_username)
{
	std::cout << "new user fd = " << user_fd << "; username =" << username << std::endl;
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

void	Users::setNick(std::string nick) {
	user_nick = nick;
}