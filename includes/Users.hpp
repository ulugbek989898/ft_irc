/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Users.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:09:22 by uisroilo          #+#    #+#             */
/*   Updated: 2023/03/28 13:32:08 by uisroilo         ###   ########.fr       */
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
	
public:
	Users(int fd, std::string pre_nick, std::string pre_username);
	void	setNick(std::string nick);
	std::string	getUserNick(void) const;
	std::string	getUserName(void) const;
	int			getUserFd(void) const;
	~Users();
};

#endif