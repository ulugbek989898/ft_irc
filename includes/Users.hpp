/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Users.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:09:22 by uisroilo          #+#    #+#             */
/*   Updated: 2023/04/11 15:52:57 by uisroilo         ###   ########.fr       */
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
	std::string	password;
	bool		isAuth;
	std::string	u_buffer;

	bool	isOPER;
	std::vector<std::string>	ChannelList;
	std::vector<std::string>	orderAuth;

public:
	Users(int fd, std::string pre_nick, std::string pre_username);
	std::string	getUserNick(void) const;
	std::string	getUserName(void) const;
	std::string	getPassword(void) const;
	void		setNick(std::string nick);
	void		setUsername(std::string pre_username);
	void		setPassword(std::string pass);
	int			getUserFd(void) const;

	bool		getUserOPER(void) const;
	void		setOPER(bool val);
	std::vector<std::string>	getChannelList() const;
	void		addChannel(std::string str);
	void		appendMsg(std::string str);
	std::string	getUserBuffer();
	void		setUserBuffer();
	bool		getIsAuth() const;
	void		setIsAuth(bool val);
	void		addOrder(std::string str);
	std::vector<std::string>		getOrder();

	~Users();
};

#endif
