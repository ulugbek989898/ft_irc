/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:25:17 by uisroilo          #+#    #+#             */
/*   Updated: 2023/04/06 08:00:29 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVMSG_HPP
# define PRIVMSG_HPP

#include <string>
#include <iostream>
#include<unistd.h>
#include <sstream>
#include <vector>
#include <stdexcept>
#include "Users.hpp"
#include "Reply.hpp"
#include <sys/socket.h>


class PRIVMSG
{
private:
	std::string					servername;
	std::vector<std::string>	privmsgCmdArr;
	std::vector<std::string>	usersChannelsArr;
	// char						buffer[256];
public:
	PRIVMSG(/* args */);
	~PRIVMSG();
	std::string	getServername();
	void	parsePrivmsg(std::string str, std::vector<Users> _Users, int newFd) throw(std::runtime_error);
	void	adv_tokenizer(std::string s, char del);
	bool	checkNickExist(std::vector<Users>	_User, std::string nick);
	std::string	getPreNickWithFd(std::vector<Users>	_Users, int fd);
};

#endif