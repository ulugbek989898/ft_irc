/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channels.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 08:09:12 by uisroilo          #+#    #+#             */
/*   Updated: 2023/04/03 11:49:03 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNELS_HPP
# define CHANNELS_HPP

#include <iostream>
#include <string>
#include "Users.hpp"

class Channels
{
private:
	std::string			ch_name;
	
public:
	Channels(std::string name);
	~Channels();
};

#endif