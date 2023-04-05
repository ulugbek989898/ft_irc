/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_JOIN.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrangwan <rrangwan@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 16:22:47 by uisroilo          #+#    #+#             */
/*   Updated: 2023/04/03 18:29:20 by rrangwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/JOIN.hpp"

JOIN::JOIN(/* args */)
{
}

JOIN::~JOIN()
{
}


void	JOIN::parseJoin(std::string str, std::vector<Users>	_User, int fd) throw(std::runtime_error)
{
	std::stringstream	ss(str);
	std::string			word;
	int					counter = 0;

	joinCmdArr.clear();

	while (ss >> word)
	{
		joinCmdArr.push_back(word);
		counter++;
	}
	std::cout << "res = " << counter <<std::endl;
	if (counter < 2) {
		joinCmdArr.clear();
		throw std::runtime_error(ERR_NEEDMOREPARAMS(getServername(), getPreNickWithFd(_User, fd), "JOIN"));
	}

	joinCmdArr2.clear();

	size_t pos = 0;
	std::string token;
	std::string s(joinCmdArr[1]);
	counter = 0;
	while ((pos = s.find(",")) != std::string::npos)
	{
		token = s.substr(0, pos);
		joinCmdArr2.push_back(token);
		//std::cout << token << std::endl;
		s.erase(0, pos + 1);
		counter++;
	}
	//NEW CODE HERE

	token = s.substr(0, std::string::npos);
	joinCmdArr2.push_back(token);	

}

int				JOIN::getSizeJoiners()
{
	return	joinCmdArr2.size();
}

std::string		JOIN::getJoinName(int n)
{
	if (n < getSizeJoiners())
		return	joinCmdArr2[n];
	else
		return NULL;
}
