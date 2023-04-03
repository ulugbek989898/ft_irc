/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QUIT.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 14:30:27 by uisroilo          #+#    #+#             */
/*   Updated: 2023/04/02 14:54:01 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/QUIT.hpp"

QUIT::QUIT(/* args */)
{
	servername = SERVER_NAME;
}

std::string		QUIT::getServername() {
	return servername;
}

QUIT::~QUIT()
{
}

std::string	QUIT::getPreNickWithFd(std::vector<Users>	_Users, int fd) {
	for (size_t i = 0; i < _Users.size(); i++) {
			if (_Users[i].getUserFd() == fd) {
				return _Users[i].getUserNick();
			}
		}
	return "";
}

void	QUIT::parseQuit(std::string str, std::vector<Users>	_User, int fd) throw(std::runtime_error) {
	std::stringstream	ss(str);
	std::string			word;
	int					counter = 0;

	quitCmdArr.clear();

	while (ss >> word) {
		quitCmdArr.push_back(word);
		counter++;
	}
	
	std::string tmp;
	if (counter > 1) {
		for (int j = 1; j < counter; j++) {
			if (j != counter - 1)
				tmp += quitCmdArr[j] + " ";
			else
				tmp += quitCmdArr[j];
		}
	}
	else
		tmp = "";

	memset(&buffer, 0, sizeof(buffer));
	tmp = ERROR(getServername(), getPreNickWithFd(_User, fd), tmp);
	tmp.copy(buffer, sizeof(buffer));
	
	for (size_t i = 0; i < _User.size(); i++) {
		if (_User[i].getUserFd() == fd) {
			if (send(fd, buffer, tmp.length() , 0) == -1) {
				perror("send");
			}
		}
	}
}
