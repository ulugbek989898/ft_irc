/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 07:05:48 by uisroilo          #+#    #+#             */
/*   Updated: 2023/03/24 09:23:57 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

// Return a listening socket
int	Server::get_listener_socket(void)
{
	int listener;	 // Listening socket descriptor
	int yes=1;		// For setsockopt() SO_REUSEADDR, below
	int rv;

	struct addrinfo hints, *ai, *p;

	// Get us a socket and bind it
	memset(&hints, 0, sizeof hints);
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

void			Server::checkStatusAndThrow(int exitCode, std::string msg) throw(std::runtime_error){
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

void			Server::setUpPoll(){
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
	
	// Add the listener to set
	setUpPoll();
	
}

void Server::add_to_pollfds()
{
	clientSockets.push_back(createPollStruct(_newFd, POLLIN));
	_fdCount++;
	
	for (int i = 0; i < _fdCount; i++) {
		printf("fd's = %d\n", clientSockets[i].fd);
	}
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

void	Server::run() {
	for(;;) {
	int poll_count = poll(&clientSockets[0], _fdCount, -1);

	checkStatusAndThrow(poll_count, POL_ERR);

	// Run through the existing connections looking for data to read
	for(int i = 0; i < _fdCount; i++) {

		// Check if someone's ready to read
		if (clientSockets[i].revents & POLLIN) { // We got one!!

			if (clientSockets[i].fd == _listener) {
				// If listener is ready to read, handle new connection

				_addrlen = sizeof(_remoteaddr);
				_newFd = accept(_listener, (struct sockaddr *)&_remoteaddr, &_addrlen);

				if (_newFd == -1) {
					perror("accept");
				} else {
					add_to_pollfds();
					
					printf("pollserver: new connection from %s on "
						"socket %d\n",
						inet_ntop(_remoteaddr.ss_family,
							get_in_addr((struct sockaddr*)&_remoteaddr),
							remoteIP, INET6_ADDRSTRLEN),
						_newFd);
				}
			} else {
				// If not the listener, we're just a regular client
				printf("heyyy1\n");
				int nbytes = recv(clientSockets[i].fd, _buf, sizeof(_buf), 0);

				int sender_fd = clientSockets[i].fd;

				if (nbytes <= 0) {
					// Got error or connection closed by client
					if (nbytes == 0) {
						// Connection closed
						printf("pollserver: socket %d hung up\n", sender_fd);
					} else {
						perror("recv");
					}

					close(clientSockets[i].fd); // Bye!

					del_from_pollfds(clientSockets[i].fd);

				} else {
					// We got some good data from a client

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
			} // END handle data from client
		} // END got ready-to-read from poll()
	} // END looping through file descriptors
} // END for(;;)--and you thought it would never end!

}

Server::~Server()
{
}