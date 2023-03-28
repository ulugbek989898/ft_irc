/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InitialParse.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:37:38 by uisroilo          #+#    #+#             */
/*   Updated: 2023/03/27 13:07:07 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/InitialParse.hpp"

bool	InitialParse::checkValidPort(std::string port) {
	int					temp_port;
	std::stringstream	sstream;
	sstream << port;
	for (size_t i = 0; i < port.length(); i++) {
		if (!isdigit(port[i]))
			return false;
	}
	sstream >> temp_port;
	if (temp_port < 1024 || temp_port > 65535)
		return false;
	return true;
}
InitialParse::InitialParse(int argc, char **argv) throw(std::runtime_error) {
	if (argc != 3)
		throw std::runtime_error(ARG_NUM_ERR);
	if (checkValidPort(argv[1]) == false)
		throw std::runtime_error(INV_PORT_ERR);
	
	std::stringstream	sstream;
	sstream << argv[1];
	sstream >> this->_port;
	this->_password = argv[2];
	
}

InitialParse::~InitialParse()
{
}

int		InitialParse::getPort() const {
	return this->_port;
}

std::string		InitialParse::getPassword() const {
	return this->_password;
}
