/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 09:08:17 by uisroilo          #+#    #+#             */
/*   Updated: 2023/04/04 17:56:57 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOIN_HPP
# define JOIN_HPP

#include <string>
#include <iostream>
#include <sys/socket.h>
#include<unistd.h>
#include <sstream>
#include <vector>
#include <stdexcept>
#include "Users.hpp"
#include "Reply.hpp"

class JOIN
{
private:
	/* data */
	std::string					servername;
	std::vector<std::string>	joinCmdArr;
	std::vector<std::string>	ChannelsArr;
public:
	JOIN(/* args */);
	~JOIN();
	void	parseJoin(std::string str, std::vector<Users>	_User, int fd) throw(std::runtime_error);
	void	adv_tokenizer(std::string s, char del, std::vector<Users>	_User, int fd);
	std::string	getServername();
	std::vector<std::string>	getChannelsArr();
	std::string	getPreNickWithFd(std::vector<Users>	_Users, int fd);

};

#endif