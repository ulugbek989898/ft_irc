/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SQUIT.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 16:18:50 by uisroilo          #+#    #+#             */
/*   Updated: 2023/04/07 16:23:01 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SQUIT_HPP
# define SQUIT_HPP

#include "Users.hpp"
#include <string>
#include <cstring>
#include <iostream>
#include<unistd.h>
#include <sstream>
#include <vector>
#include <stdexcept>
#include "Reply.hpp"
#include <sys/socket.h>

class SQUIT
{
private:
	std::string					servername;
	std::vector<std::string>	squitCmdArr;
	char						buffer[256];
public:
	SQUIT(/* args */);
	~SQUIT();
	void		parseSquit(std::string str, std::vector<Users>	_User, int fd, std::string _servername) throw(std::runtime_error);
	std::string	getServerName();
	std::string	getPreNickWithFd(std::vector<Users>	_Users, int fd);
	bool		getIsOperWithFd(std::vector<Users>	_Users, int fd);
};

#endif