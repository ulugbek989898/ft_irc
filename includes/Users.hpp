/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Users.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrangwan <rrangwan@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:09:22 by uisroilo          #+#    #+#             */
/*   Updated: 2023/03/31 19:11:00 by rrangwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USERS_HPP
# define USERS_HPP

#include <iostream>

class Users
{
private:
	int	user_fd;
	std::string	user_nick;
	std::string	username;

	bool	isOPER;

public:
	Users(int fd, std::string pre_nick, std::string pre_username);
	void	setNick(std::string nick);
	void	setUsername(std::string nick);
	std::string	getUserNick(void) const;
	std::string	getUserName(void) const;
	int			getUserFd(void) const;

	bool	getUserOPER(void) const;
	void	setOPER(bool val);

	~Users();
};

#endif
