/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Users.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:09:22 by uisroilo          #+#    #+#             */
/*   Updated: 2023/04/05 07:55:02 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USERS_HPP
# define USERS_HPP

#include <iostream>
#include <vector>

class Users
{
private:
	int	user_fd;
	std::string	user_nick;
	std::string	username;

	bool	isOPER;
	std::vector<std::string>	ChannelList;

public:
	Users(int fd, std::string pre_nick, std::string pre_username);
	std::string	getUserNick(void) const;
	std::string	getUserName(void) const;
	void		setNick(std::string nick);
	void		setUsername(std::string nick);
	int			getUserFd(void) const;

	bool		getUserOPER(void) const;
	void		setOPER(bool val);
	std::vector<std::string>	getChannelList() const;
	void		addChannel(std::string str);

	~Users();
};

#endif
