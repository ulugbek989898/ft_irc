#ifndef SERVER_HPP
# define SERVER_HPP

#define LISTEN_ERR "error getting listening socket\n"
#define POL_ERR "Error: poll()"

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <poll.h>

#include <vector>
#include <sstream>
#include <iostream>
#include <stdexcept>

class Server
{
private:
	int							_port;
	std::string					_password;
	int							_listener;	// // Listening socket descriptor 
	int							_newFd;		// Newly accept()ed socket descriptor
	struct	sockaddr_storage	_remoteaddr; // Client address
	socklen_t					_addrlen;
	char						_buf[256];    // Buffer for client data
	char						remoteIP[INET6_ADDRSTRLEN];
	
	int							_fdCount;
	std::vector<struct pollfd>	clientSockets;

public:
	Server(int port, std::string password);
	int				get_listener_socket(void);
	void			checkStatusAndThrow(int exitCode, std::string msg) throw(std::runtime_error);
	void			setUpPoll();
	struct pollfd	createPollStruct(int fd, short events);

	void			run();
	void			add_to_pollfds();
	void			*get_in_addr(struct sockaddr *sa);
	void			del_from_pollfds(int fd);
	~Server();
};

#endif