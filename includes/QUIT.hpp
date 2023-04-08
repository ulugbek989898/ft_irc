/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QUIT.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 14:29:49 by uisroilo          #+#    #+#             */
/*   Updated: 2023/04/07 15:55:46 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUIT_HPP
# define QUIT_HPP

#include <string>
#include <cstring>
#include <iostream>
#include<unistd.h>
#include <sstream>
#include <vector>
#include <stdexcept>
#include "Users.hpp"
#include "Reply.hpp"
#include <sys/socket.h>

class QUIT
{
private:
	std::string					servername;
	std::vector<std::string>	quitCmdArr;
	char						buffer[256];
public:
	QUIT(/* args */);
	~QUIT();
	std::string	getServername();
	void		parseQuit(std::string str, std::vector<Users>	_User, int fd, std::string _servername) throw(std::runtime_error);
	std::string	getPreNickWithFd(std::vector<Users>	_Users, int fd);
};

#endif