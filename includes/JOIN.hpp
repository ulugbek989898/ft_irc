
#ifndef JOIN_HPP
# define JOIN_HPP

#include <string>
#include <iostream>
#include<unistd.h>
#include <sstream>
#include <vector>
#include <stdexcept>
#include "Users.hpp"
#include "Reply.hpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <poll.h>

#include "KILL.hpp"


class JOIN: public KILL
{
private:

	std::vector<std::string>	joinCmdArr;
	std::vector<std::string>	joinCmdArr2;



public:
	JOIN(/* args */);
	~JOIN();

	void		parseJoin(std::string str, std::vector<Users>	_User, int fd) throw(std::runtime_error);

	int			getSizeJoiners();
	std::string	getJoinName(int n);

};

#endif
