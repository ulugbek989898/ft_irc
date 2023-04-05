/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Users.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrangwan <rrangwan@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:09:22 by uisroilo          #+#    #+#             */
/*   Updated: 2023/04/03 18:07:47 by rrangwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USERS_HPP
# define USERS_HPP

#include <iostream>
#include <vector>
#include <string>

class Users
{
private:
	int	user_fd;
	std::string	user_nick;
	std::string	username;

	bool	isOPER;

	std::vector<std::string>	listChannels;

public:
	Users(int fd, std::string pre_nick, std::string pre_username);
	std::string	getUserNick(void) const;
	std::string	getUserName(void) const;
	void		setNick(std::string nick);
	void		setUsername(std::string nick);
	int			getUserFd(void) const;

	bool		getUserOPER(void) const;
	void		setOPER(bool val);

	bool		IsinChannel(std::string ch_name);
	void		addUsertoChannel(std::string ch_name);

	~Users();
};

#endif
