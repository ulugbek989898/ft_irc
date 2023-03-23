/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InitialParse.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:29:34 by uisroilo          #+#    #+#             */
/*   Updated: 2023/03/22 18:27:22 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INITIALPARSE_HPP
# define INITIALPARSE_HPP

# define ARG_NUM_ERR "Invalid number of arguments, it must :./ircserv 6667 password"
# define INV_PORT_ERR "Invalid port, it must greater than 1024, and less than 65536 - 1"

#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>


class InitialParse
{
private:
	int			_port;
	std::string	_password;
public:
	InitialParse(int argc, char **argv) throw(std::runtime_error);
	bool			checkValidPort(std::string port);
	int				getPort() const;
	std::string		getPassword() const;
	~InitialParse();
};

#endif