/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:25:17 by uisroilo          #+#    #+#             */
/*   Updated: 2023/04/06 18:10:12 by uisroilo         ###   ########.fr       */
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
#include "Channels.hpp"
#include "Reply.hpp"
#include <sys/socket.h>


class PRIVMSG
{
private:
	std::string					servername;
	std::vector<std::string>	privmsgCmdArr;
	std::vector<std::string>	usersChannelsArr;
	std::string					msgSend;
	bool						isUser;
	bool						isChannel;

	// char						buffer[256];
public:
	PRIVMSG(/* args */);
	~PRIVMSG();
	std::string			getServername();
	void				parsePrivmsg(std::string str, std::vector<Users> _Users, std::vector<Channels> _Channels, int newFd) throw(std::runtime_error);
	void				adv_tokenizer(std::string s, char del);
	bool				checkNickExist(std::vector<Users>	_User, std::string nick);
	bool				checkChannelExist(std::vector<Channels>	_Channels, std::string nick);
	
	std::vector<int>	getChannelUserFds(std::vector<Channels> _Channels, std::string channel);
	std::string			getPreNickWithFd(std::vector<Users>	_Users, int fd);
	int					getFdFromUsers(std::string nick, std::vector<Users> _Users) const;
};

#endif