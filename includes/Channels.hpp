/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channels.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrangwan <rrangwan@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 08:09:12 by uisroilo          #+#    #+#             */
/*   Updated: 2023/04/03 19:30:08 by rrangwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNELS_HPP
# define CHANNELS_HPP

#include <iostream>
#include <string>
#include <vector>
//#include <map>

#include "Users.hpp"


#define MAX_USERS 5

class Channels
{
private:
	std::string			ch_name;

	int					numUsers;
	std::vector<int>	listUsers;

	//std::map<int, std::string>	listUsers2;



public:
	Channels(std::string name);
	~Channels();


	std::string		getName() const;

	void			setUsers(int size);
	int				getUsers() const;

	int				getlistUsers(int i);

	void			addUsertolist(int fd);

	std::vector<int>	getALLlistUsers();



};

#endif
