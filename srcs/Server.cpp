/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 07:05:48 by uisroilo          #+#    #+#             */
/*   Updated: 2023/04/12 06:57:52 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

// Return a listening socket

void Server::terminateServer() {
	stopServer = true;
}

int	Server::get_listener_socket(void)
{
	int listener;	 // Listening socket descriptor
	int yes = 1;		// For setsockopt() SO_REUSEADDR, below
	int rv;

	char hostname[128];

	gethostname(hostname, sizeof hostname);
	printf("My hostname: %s\n", hostname);
	_servername = hostname;

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
	stopServer = false;
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
	_Users.push_back(Users(_newFd, "", ""));
	std::cout << "size=" << _Users.size() << std::endl;
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

void	Server::requestFromServerToAuthonticate(int newUserFd, int userIndex) {
	int 		status;
	std::string msg;

	try
	{
		memset(&_buf, 0, sizeof(_buf));
		int nbytes = recv(newUserFd, _buf, sizeof(_buf), 0);
		if (nbytes <= 0)
		{
			if (nbytes == 0)
				throw std::runtime_error("Connection closed");
			else
				throw std::runtime_error("Recievingg1") ;
		}
		for (size_t i = 0; i < _Users.size(); i++) {
			if (_Users[i].getUserFd() == newUserFd) {
				_Users[i].appendMsg(_buf);
				std::string	tmp = _Users[i].getUserBuffer();
				if (tmp[tmp.size() - 1] != '\n')
					return ;
			}
		}
		
		std::string str = getUserBufferWithFd(_Users, newUserFd);
		for (size_t i = 0; i < _Users.size(); i++)
		{
			if (_Users[i].getUserFd() == newUserFd) {
				_Users[i].setUserBuffer();
				break ;
			}
		}
		std::stringstream	ss(str);
		std::string			word;
		int					counter = 0;

		while (ss >> word) {
			tmpBuf.push_back(word);
			counter++;
		}
		if (counter > 1) {
			ft_parse(newUserFd, tmpBuf[0], str);
			if (_Users[userIndex].getPassword().empty() && tmpBuf[0] == "PASS") {
				_Users[userIndex].addOrder(tmpBuf[0]);
				_Users[userIndex].setPassword(cmdParse.getPrePassword());
				cmdParse.setPrePassword("");
			}
			if (_Users[userIndex].getUserNick().empty() && tmpBuf[0] == "NICK") {
				_Users[userIndex].addOrder(tmpBuf[0]);
				_Users[userIndex].setNick(cmdParse.getPreNick());
				ft_print_users();
				cmdParse.setPreNick("");
			}
			if (_Users[userIndex].getUserName().empty() && tmpBuf[0] == "USER") {
				_Users[userIndex].addOrder(tmpBuf[0]);
				_Users[userIndex].setUsername(cmdParse.getPreUsername());
				ft_print_users();
				cmdParse.setPreUsername("");
			}
			if (!_Users[userIndex].getUserNick().empty() && !_Users[userIndex].getUserName().empty() && !_Users[userIndex].getPassword().empty()) {
				checkOrder(userIndex);
				_Users[userIndex].setIsAuth(true);
				ft_print_users();
				msg = "001 " + _Users[userIndex].getUserNick() + " :Welcome to the Internet Relay Network " + _Users[userIndex].getUserNick() + "\r\n";
				status = send(newUserFd, msg.c_str(), msg.length(), 0);
				msg.clear();
				checkStatusAndThrow(status, SEND_ERR);
				showGeneralGuide(newUserFd, _Users, userIndex);
			}
			tmpBuf.clear();
		}
		else {
			std::cout << "str = " << str << ", counter = " << counter << "\n";
			throw std::runtime_error("Params not enough");
		}
	}
	catch(const std::exception& e)
	{
		tmpBuf.clear();
		cmdParse.setPreNick("");
		cmdParse.setPreUsername("");
		cmdParse.setPrePassword("");
		msg = e.what();
		msg += "\r\n";
		status = send(newUserFd, msg.c_str(), msg.length(), 0);
		close(newUserFd);
		removeUserFromVector(newUserFd);
		del_from_pollfds(newUserFd);
		ft_print_users();
	}
}

void	Server::NewConnection(void) {
	// If listener is ready to read, handle new connection

	_addrlen = sizeof(_remoteaddr);
	_newFd = accept(_listener, (struct sockaddr *)&_remoteaddr, &_addrlen);
	std::cout << "fddd = " << _newFd << std::endl;
	if (_newFd == -1)
		std::cout << "accept\n";
	makeFdNonBlock(_newFd);
	add_to_pollfds();
	std::cout << "Server: new connection, newFd = " << _newFd << std::endl;
	ft_show_auth_usage(_newFd);
}

void	Server::ExistingConnection(int indexFd) {
		// If not the listener, we're just a regular client
	if (_Users[indexFd - 1].getIsAuth()) {
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
				std::cout << "recv\n";
			close(clientSockets[indexFd].fd);
			del_from_pollfds(clientSockets[indexFd].fd);
		}
		else {
			// We got some good data from a client
			for (size_t i = 0; i < _Users.size(); i++) {
				if (_Users[i].getUserFd() == sender_fd) {
					_Users[i].appendMsg(_buf);
					std::string	tmp = _Users[i].getUserBuffer();
					if (tmp[tmp.size() - 1] != '\n')
						return ;
				}
			}
			
			std::string str = getUserBufferWithFd(_Users, sender_fd);
			// setUserBufferWithFd(_Users, sender_fd);
			for (size_t i = 0; i < _Users.size(); i++)
			{
				if (_Users[i].getUserFd() == sender_fd) {
					_Users[i].setUserBuffer();
					break ;
				}
			}
			// std::cout << "we are=" << getUserBufferWithFd(_Users, sender_fd);
			cmdParse.parse(str, _Users, _Channels, clientSockets[indexFd].fd, this->_servername);
			str.clear();
			if (cmdParse.getCmd() == "NICK")
			{
				msg = ":" + getNickFromUsers(clientSockets[indexFd].fd) + "!~" + cmdParse.getPreUsername() + "@" + getServername() + " NICK :" + cmdParse.getPreNick() + "\r\n";
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
				int	tmp_Fd = cmdParse.getFdFromUsers(cmdParse.getNickWithIndex(1), _Users);
				for (size_t i = 0; i < _Users.size(); i++) {
					if (_Users[i].getUserFd() == tmp_Fd) {
						for (size_t k = 0; k < _Users[i].getChannelList().size(); k++) {
							for (size_t j = 0; j < this->_Channels.size(); j++) {
								if (this->_Channels[j].getChannelName() == _Users[i].getChannelList()[k]) {
									this->_Channels[j].removeUserFd(tmp_Fd);
									break;
								}
							}
						}
					}
				}
				close (cmdParse.getFdFromUsers(cmdParse.getNickWithIndex(1), _Users));
				del_from_pollfds(cmdParse.getFdFromUsers(cmdParse.getNickWithIndex(1), _Users));
				removeUserFromVector(cmdParse.getFdFromUsers(cmdParse.getNickWithIndex(1), _Users));
				ft_print_users();
			}
			else if (cmdParse.getCmd() == "QUIT") {
				for (size_t k = 0; k < _Users[indexFd - 1].getChannelList().size(); k++) {
					for (size_t j = 0; j < this->_Channels.size(); j++) {
						if (this->_Channels[j].getChannelName() == _Users[indexFd - 1].getChannelList()[k]) {
							this->_Channels[j].removeUserFd(clientSockets[indexFd].fd);
							break;
						}
					}
				}
				close (clientSockets[indexFd].fd);
				del_from_pollfds(sender_fd);
				removeUserFromVector(sender_fd);
				ft_print_users();
			}
			else if (cmdParse.getCmd() == "JOIN") {
				std::vector<std::string>	tmp = cmdParse.getJOIN().getChannelsArr();

				for (size_t i = 0; i < tmp.size(); i++) {
					if (!checkUserInChannel(tmp[i], clientSockets[indexFd].fd)) {
						this->_Users[indexFd - 1].addChannel(tmp[i]);
						if (checkChannelExistInChannelList(tmp[i])) {
							for (size_t j = 0; j < this->_Channels.size(); j++) {
								if (this->_Channels[j].getChannelName() == tmp[i]) {
									this->_Channels[j].setUserFd(clientSockets[indexFd].fd);
									break;
								}
							}
						}
						else
							this->_Channels.push_back(Channels(tmp[i], clientSockets[indexFd].fd));
					}
				}
				tmp.clear();
			}
			
			ft_print_users();
			ft_print_Channels_Users();
		}
	}
	else {
		requestFromServerToAuthonticate(_Users[indexFd - 1].getUserFd(), indexFd - 1);
	}
}

void	Server::run() {
	while (!stopServer)
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
	//this->~Server();
}

Server::~Server()
{
	for (std::vector<struct pollfd>::iterator it = clientSockets.begin(); it != clientSockets.end(); it++) {
		close(it->fd);
	}
	std::cout << "\nServer has been terminated." << std::endl;
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
		close(i + 3);
}
