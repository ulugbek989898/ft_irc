/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channels.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 08:12:22 by uisroilo          #+#    #+#             */
/*   Updated: 2023/04/07 08:23:16 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Channels.hpp"

Channels::Channels(std::string name, int fd) : ch_name(name)
{
	this->userFds.push_back(fd);
}

Channels::~Channels()
{
}

void	Channels::setUserFd(int fd) {
	for (size_t i = 0; i < this->userFds.size(); i++) {
		if (this->userFds[i] == fd)
			return;
	}
	this->userFds.push_back(fd);
}

void	Channels::removeUserFd(int fd) {
	for (std::vector<int>::iterator it = userFds.begin(); it!= userFds.end(); it++)
	{
		if (fd == *it) {
			userFds.erase(it);
			break ;
		}
	}
}

std::string	Channels::getChannelName() const {
	return this->ch_name;
}

std::vector<int>	Channels::getChannelUserFds() {
	return this->userFds;
}