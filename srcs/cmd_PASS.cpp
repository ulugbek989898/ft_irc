/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_PASS.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 14:24:59 by uisroilo          #+#    #+#             */
/*   Updated: 2023/04/01 14:25:13 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CommandParse.hpp"

void	CommandParse::parsePass(std::string str, std::string password) throw(std::runtime_error) {
	std::stringstream	ss(str);
	std::string			word;
	int					counter = 0;

	this->_password = password;

	while (ss >> word) {
		passwordArr.push_back(word);
		counter++;
	}
	if (counter != 2) {
		passwordArr.clear();
		throw std::runtime_error("Not enough parameters");
	}

	if (passwordArr[0] == "PASS")
	{
		if (password == passwordArr[1]) {
			std::cout << "password correct" <<std::endl;

		}
		else {
			passwordArr.clear();
			throw std::runtime_error(ERR_PASSWDMISMATCH);
		}
	}
	else {
		passwordArr.clear();
		throw std::runtime_error(CMD_PASS_ERR);
	}
	passwordArr.clear();
}
