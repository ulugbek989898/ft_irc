/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channels.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 08:09:12 by uisroilo          #+#    #+#             */
/*   Updated: 2023/04/07 08:19:06 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNELS_HPP
# define CHANNELS_HPP

#include <iostream>
#include <string>
#include <vector>

class Channels
{
private:
	std::string			ch_name;
	std::vector<int>	userFds;
	
public:
	Channels(std::string name, int fd);
	void	setUserFd(int fd);
	void	removeUserFd(int fd);
	std::string	getChannelName() const;
	std::vector<int>	getChannelUserFds();
	~Channels();
};

#endif