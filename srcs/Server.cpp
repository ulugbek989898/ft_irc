/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrangwan <rrangwan@42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 07:05:48 by uisroilo          #+#    #+#             */
/*   Updated: 2023/04/04 02:52:22 by rrangwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

// Return a listening socket
int	Server::get_listener_socket(void)
{
	int listener;	 // Listening socket descriptor
	int yes = 1;		// For setsockopt() SO_REUSEADDR, below
	int rv;

	struct addrinfo hints, *ai, *p;

	// Get us a socket and bind it
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	std::stringstream	ss;
	ss << _port;
	std::string const str_port = ss.str();

	if ((rv = getaddrinfo(NULL, str_port.c_str(), &hints, &ai)) != 0) {
		std::cout << "selectserver: " << gai_strerror(rv) << std::endl;
		exit(1);
	}

	for(p = ai; p != NULL; p = p->ai_next) {
		listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (listener < 0) {
			continue;
		}

		// Lose the pesky "address already in use" error message
		setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

		if (bind(listener, p->ai_addr, p->ai_addrlen) < 0) {
			close(listener);
			continue;
		}
		break;
	}

	// If we got here, it means we didn't get bound
	if (p == NULL) {
		return -1;
	}

	freeaddrinfo(ai); // All done with this

	// Listen
	if (listen(listener, 10) == -1) {
		return -1;
	}

	return listener;
}

void	Server::checkStatusAndThrow(int exitCode, std::string msg) throw(std::runtime_error){
	if (exitCode < 0)
		throw std::runtime_error(msg);
}

struct pollfd	Server::createPollStruct(int fd, short events){
	struct pollfd temp;

	temp.fd = fd;
	temp.events = events;
	temp.revents = 0;

	return temp;
}

void	Server::setUpPoll(){
	_fdCount = 1;
	clientSockets.push_back(createPollStruct(_listener, POLLIN));
}



Server::Server(int port, std::string password)
{
	_port = port;
	_password = password;

	// Set up and get a listening socket
	_listener = get_listener_socket();
	checkStatusAndThrow(_listener, LISTEN_ERR);
	std::cout << "server: waiting for connections...\n";
	// Add the listener to set
	setUpPoll();

}

std::string		Server::getPassword() const {
	return (_password);
}

void Server::add_to_pollfds()
{
	clientSockets.push_back(createPollStruct(_newFd, POLLIN));
	_Users.push_back(Users(_newFd, cmdParse.getPreNick(), cmdParse.getPreUsername()));
	_fdCount++;
	ft_print_users();
}

void *Server::get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

void	Server::del_from_pollfds(int fd){
	for (std::vector<struct pollfd>::iterator it = clientSockets.begin(); it != clientSockets.end(); it++){
		if (it->fd == fd)
		{
			clientSockets.erase(it);
			_fdCount--;
			break ;
		}
	}
}

void	Server::makeFdNonBlock(int fd) throw(std::runtime_error){
	int status;

	status = fcntl(fd, F_SETFL, O_NONBLOCK);
	checkStatusAndThrow(status, FCNTL_ERR);
}

bool	Server::requestFromServerToAuthonticate(int newUserFd) {
	int 		status;
	std::string msg;
	// msg = PURPLE;

	try
	{
		ft_show_auth_usage(newUserFd);

		ft_parse(newUserFd, "PASS");
		ft_parse(newUserFd, "NICK");
		ft_parse(newUserFd, "USER");

		msg = "001 " + cmdParse.getPreNick() + " :Welcome to the Internet Relay Network " + cmdParse.getPreNick() + "\r\n";
		status = send(newUserFd, msg.c_str(), msg.length(), 0);
		checkStatusAndThrow(status, SEND_ERR);
	}
	catch(const std::exception& e)
	{
		msg = e.what();
		msg += "\r\n";
		status = send(newUserFd, msg.c_str(), msg.length(), 0);
		close(newUserFd);
		return false;
	}
	return true;
}

void	Server::NewConnection(void) {
	// If listener is ready to read, handle new connection

	_addrlen = sizeof(_remoteaddr);
	_newFd = accept(_listener, (struct sockaddr *)&_remoteaddr, &_addrlen);

	if (_newFd == -1)
		perror("accept");
	else if (requestFromServerToAuthonticate(_newFd)) {
		makeFdNonBlock(_newFd);
		add_to_pollfds();
		std::cout << "Server: new connection, newFd = " << _newFd << std::endl;
		showGeneralGuide(_newFd);
	}
}

void	Server::ExistingConnection(int indexFd) {
		// If not the listener, we're just a regular client
	std::string	msg;

	memset(&_buf, 0, sizeof(_buf));
	int nbytes = recv(clientSockets[indexFd].fd, _buf, sizeof(_buf), 0);

	int sender_fd = clientSockets[indexFd].fd;

	if (nbytes <= 0) {
		// Got error or connection closed by client
		if (nbytes == 0) {
			// Connection closed
			std::cout << "pollserver: socket " << sender_fd << " hung up\n";
			removeUserFromVector(sender_fd);
			ft_print_users();
		} else
			perror("recv");
		close(clientSockets[indexFd].fd);
		del_from_pollfds(clientSockets[indexFd].fd);
	} else {
		// We got some good data from a client
		cmdParse.parse(_buf, _Users, clientSockets[indexFd].fd);
		if (cmdParse.getCmd() == "NICK")
		{
			msg = ":" + getNickFromUsers(clientSockets[indexFd].fd) + "!~" + cmdParse.getPreUsername() + "@localhost NICK :" + cmdParse.getPreNick() + "\r\n";
			int status = send(clientSockets[indexFd].fd, msg.c_str(), msg.length(), 0);
			checkStatusAndThrow(status, SEND_ERR);
			updateNickFromVector(clientSockets[indexFd].fd, cmdParse.getPreNick());
			ft_print_users();
		}
		else if (cmdParse.getCmd() == "OPER")
		{
			this->setIsOperWithFd(cmdParse.getIsOper(), clientSockets[indexFd].fd);
			ft_print_users();
		}
		else if (cmdParse.getCmd() == "KILL")
		{
			//remove user from database also pollfd socket, using his nickname
			close (cmdParse.getFdFromUsers(cmdParse.getNickWithIndex(1), _Users));
			del_from_pollfds(cmdParse.getFdFromUsers(cmdParse.getNickWithIndex(1), _Users));
			removeUserFromVector(cmdParse.getFdFromUsers(cmdParse.getNickWithIndex(1), _Users));
			ft_print_users();
		}
		else if (cmdParse.getCmd() == "QUIT") {
			close (cmdParse.getFdFromUsers(cmdParse.getNickWithIndex(1), _Users));
			del_from_pollfds(cmdParse.getFdFromUsers(cmdParse.getNickWithIndex(1), _Users));
			removeUserFromVector(cmdParse.getFdFromUsers(cmdParse.getNickWithIndex(1), _Users));
			ft_print_users();
		}
		else if (cmdParse.getCmd() == "SQUIT") {
			clientSockets.clear();
			closeAllUserFds();
			removeAllUsersFromVector();
			ft_print_users();
			exit(0);
		}
		else if (cmdParse.getCmd() == "JOIN")
		{
			for (int i = 0; i < cmdParse.JOINgetSizeJoiners(); i++)
			{
				//std::cout << "test 1234 i = "<< i <<"size =  "<<  cmdParse.JOINgetSizeJoiners()<<"fd = "<< clientSockets[indexFd].fd<<" \n";
			if (addNewChannelJOIN(cmdParse.JOINgetJoinName(i)))  //0 if fail 2 if already exist 1 if new created
				{
					if (addFDtoChannelJOIN(cmdParse.JOINgetJoinName(i), clientSockets[indexFd].fd))  //1 if added to channel (channel exits)
					{
						addChanneltoUSERJOIN(cmdParse.JOINgetJoinName(i),clientSockets[indexFd].fd);
						ft_print_JOIN(cmdParse.JOINgetJoinName(i), clientSockets[indexFd].fd);
					}

				}
			}

		}

		for(int j = 0; j < _fdCount; j++) {
			// Send to everyone!
			int dest_fd = clientSockets[j].fd;
			// Except the listener and ourselves
			if (dest_fd != _listener && dest_fd != sender_fd) {
				if (send(dest_fd, _buf, nbytes, 0) == -1) {
					perror("send");
				}
			}
		}
	}

}

void	Server::run() {
	while (1)
	{
		int	status = poll(&clientSockets[0], _fdCount, -1);
		checkStatusAndThrow(status, POL_ERR);
		// Run through the existing connections looking for data to read
		for(int i = 0; i < _fdCount; i++) {
			// Check if someone's ready to read
			if (clientSockets[i].revents & POLLIN) { // We got one!!
				if (clientSockets[i].fd == _listener)
					NewConnection();
				else
					ExistingConnection(i);
			}
		}
	}
}

Server::~Server()
{
}

void	Server::removeUserFromVector(int fd) {
	std::vector<Users>::iterator it = _Users.begin();
	while (it != _Users.end())
	{
		if (it->getUserFd() == fd) {
			_Users.erase(it);
			break ;
		}
		++it;
	}
}

void	Server::removeAllUsersFromVector() {
	_Users.clear();
}

void	Server::updateNickFromVector(int fd, std::string new_nick) {
	std::vector<Users>::iterator it = _Users.begin();
	while (it != _Users.end())
	{
		if (it->getUserFd() == fd) {
			it->setNick(new_nick);
			break ;
		}
		++it;
	}
}

void	Server::closeAllUserFds() {
	for (size_t i = 0; i < _Users.size(); i++)
		close(i + 5);
}


int	Server::addNewChannelJOIN(std::string	str)
{
	if((this->_Channels.size()>= 10))
	{
		std::cout << "Max channels reached \n";
		return 0;
	}
	if (str[0] != '#')
	{
		std::cout << "Channel name should start with # "<< str <<" \n";
		return 0;
	}

	std::vector<Channels>::iterator	it;

	for(it = _Channels.begin(); it != _Channels.end(); it++)
	{
		if(it->getName() == str)
		{
			std::cout << "Channel name already exists "<< str <<" \n";
			return 2;
		}
	}

	this->_Channels.push_back(Channels(str));
	std::cout << "Channel name created "<< str <<" \n";
	return 1;

}

	int			Server::addFDtoChannelJOIN(std::string str, int fd)
	{
		std::vector<Channels>::iterator	it;

		for(it = _Channels.begin(); it != _Channels.end(); it++)
		{
			if(it->getName() == str)
			{
				it->addUsertolist(fd);
				return 1;
			}
		}
		return 0;
	}

	void			Server::addChanneltoUSERJOIN(std::string str, int fd)
	{
		std::vector<Users>::iterator	it;

		for(it = _Users.begin(); it != _Users.end(); it++)
		{
			if(it->getUserFd() == fd)
			{
				if(!(it->IsinChannel(str)))
					it->addUsertoChannel(str);
				else
					std::cout << "User "<<it->getUserNick()<<" already in Channel "<< str <<" \n";
			}
		}
	}


std::vector<int> 	Server::getUserinChanellJOIN(std::string str)
{
		std::vector<int> temp;

		std::vector<Channels>::iterator	it;

		for(it = _Channels.begin(); it <= _Channels.end(); it++)
		{
			if(it->getName() == str)
			{
				return (it->getALLlistUsers());

			}
		}
		return temp;
}
