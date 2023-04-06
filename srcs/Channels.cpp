/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channels.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 08:12:22 by uisroilo          #+#    #+#             */
/*   Updated: 2023/04/06 06:54:15 by uisroilo         ###   ########.fr       */
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

std::string	Channels::getChannelName() const {
	return this->ch_name;
}

std::vector<int>	Channels::getChannelUserFds() const {
	return this->userFds;
}