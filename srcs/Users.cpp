/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Users.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrangwan <rrangwan@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:10:46 by uisroilo          #+#    #+#             */
/*   Updated: 2023/04/03 18:07:42 by rrangwan         ###   ########.fr       */
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

//false if not in channel yet
bool		Users::IsinChannel(std::string ch_name)
{
	// std::vector<std::string>::iterator	it;

	for(std::vector<std::string>::iterator	it = listChannels.begin(); it != listChannels.end(); it++)
	{
		if (*it == ch_name)
			return true;
	}
	return false;
}

void		Users::addUsertoChannel(std::string ch_name)
{
	if(ch_name[0] == '#')
	{
		// std::vector<std::string>::iterator	it;

		// for (it = listChannels.begin(); it != listChannels.end(); it++)
		// {
		// 	if(*it = fd)
		// 		return ; //to avoid duplicate fds
		// }
		// //listUsers.push_back(fd);
		listChannels.push_back(ch_name);

	}
}
