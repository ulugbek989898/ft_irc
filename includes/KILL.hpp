/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KILL.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 06:25:07 by uisroilo          #+#    #+#             */
/*   Updated: 2023/04/02 14:13:55 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KILL_HPP
# define KILL_HPP
#include <string>
#include <iostream>
#include<unistd.h>
#include <sstream>
#include <vector>
#include <stdexcept>
#include "Users.hpp"
#include "Reply.hpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <poll.h>

class KILL
{
private:
	std::string					servername;
	std::vector<std::string>	killCmdArr;
	char						buffer[256];
public:
	KILL(/* args */);
	~KILL();
	std::string	getServername();
	void		parseKill(std::string str, std::vector<Users>	_User, int fd) throw(std::runtime_error);
	std::string	getPreNickWithFd(std::vector<Users>	_Users, int fd);
	bool		getIsOperWithFd(std::vector<Users>	_Users, int fd);
	bool		checkNickExist(std::vector<Users>	_Users, std::string killedNick, int fd);
};

#endif