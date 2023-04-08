/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NOTICE.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:11:21 by uisroilo          #+#    #+#             */
/*   Updated: 2023/04/08 07:12:03 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NOTICE_HPP
# define NOTICE_HPP

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


class NOTICE
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
	NOTICE(/* args */);
	~NOTICE();
	std::string			getServername();
	void				parseNoticeMsg(std::string str, std::vector<Users> _Users, std::vector<Channels> _Channels, int newFd, std::string _servername) throw(std::runtime_error);
	void				adv_tokenizer(std::string s, char del);
	bool				checkNickExist(std::vector<Users>	_User, std::string nick);
	bool				checkChannelExist(std::vector<Channels>	_Channels, std::string nick);
	
	std::vector<int>	getChannelUserFds(std::vector<Channels> _Channels, std::string channel);
	std::string			getPreNickWithFd(std::vector<Users>	_Users, int fd);
	int					getFdFromUsers(std::string nick, std::vector<Users> _Users) const;
};

#endif