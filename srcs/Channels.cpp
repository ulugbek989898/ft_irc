/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channels.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrangwan <rrangwan@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 08:12:22 by uisroilo          #+#    #+#             */
/*   Updated: 2023/04/03 19:31:01 by rrangwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Channels.hpp"

Channels::Channels(std::string name) : ch_name(name), numUsers(0)
{
}

Channels::~Channels()
{
}


std::string		Channels::getName() const
{
	return ch_name;
}

void			Channels::setUsers(int size)
{
	numUsers = size;
}

int				Channels::getUsers() const
{
	return numUsers;
}


void Channels::addUsertolist(int fd)
{
	if (getUsers() < MAX_USERS)
	{
		int	it;

		for (it = 0; it != static_cast<int>(listUsers.size()); it++)
		{
			if(getlistUsers(it) == fd)
				return ; //to avoid duplicate fds
		}
		listUsers.push_back(fd);
		this->setUsers(getUsers() + 1);

		//listUsers2[fd] = "temp";
	}
	else
		std::cout<<"Maximum number of users reached for channel " << getName()<<std::endl;
}

int		Channels::getlistUsers(int i)
{
	return listUsers[i];
}


std::vector<int>	Channels::getALLlistUsers()
{
	std::vector<int>	temp(listUsers);
	return temp;
}
