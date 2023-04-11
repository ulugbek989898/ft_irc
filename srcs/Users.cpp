/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Users.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:10:46 by uisroilo          #+#    #+#             */
/*   Updated: 2023/04/11 15:53:15 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Users.hpp"

Users::Users(int fd, std::string pre_nick, std::string pre_username):user_fd(fd), user_nick(pre_nick), username(pre_username)
{
	// std::cout << "new user fd = " << user_fd << "; username =" << username << std::endl;
	this->isOPER = false;
	this->isAuth = false;
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

std::string	Users::getPassword(void) const {
	return password;
}

bool	Users::getUserOPER(void) const {
	return isOPER;
}


void	Users::setNick(std::string nick) {
	user_nick = nick;
}

void	Users::setUsername(std::string pre_username) {
	username = pre_username;
}

void	Users::setPassword(std::string pass) {
	password = pass;
}

void	Users::setOPER(bool val) {
	isOPER = val;
}

std::vector<std::string>	Users::getChannelList() const {
	return ChannelList;
}

void	Users::addChannel(std::string str) {
	this->ChannelList.push_back(str);
}

void	Users::appendMsg(std::string str) {
	// std::cout << "before=" << u_buffer << std::endl;
	this->u_buffer += str;
	// std::cout << "after=" << u_buffer << std::endl;
}

std::string	Users::getUserBuffer() {
	return u_buffer;
}

void	Users::setUserBuffer() {
	u_buffer.clear();
}

bool	Users::getIsAuth() const {
	return	isAuth;
}

void	Users::setIsAuth(bool val) {
	isAuth = val;
}

void		Users::addOrder(std::string str) {
	orderAuth.push_back(str);
}

std::vector<std::string>	Users::getOrder() {
	return orderAuth;
}