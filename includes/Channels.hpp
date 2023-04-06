/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channels.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 08:09:12 by uisroilo          #+#    #+#             */
/*   Updated: 2023/04/05 09:03:10 by uisroilo         ###   ########.fr       */
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
	std::string	getChannelName() const;
	std::vector<int>	getChannelUserFds() const;
	~Channels();
};

#endif