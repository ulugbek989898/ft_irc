#ifndef SERVER_HPP
# define SERVER_HPP

#define LISTEN_ERR "error getting listening socket\n"
#define POL_ERR "Error: poll()"
#define FCNTL_ERR "Error: fcntl()"
#define SEND_ERR "Error: send()"
#define SETSOCKOPT_ERR "Error: setsockopt()"
#define BIND_ERR "Error: bind()"

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
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
#include <fcntl.h>
#include <iomanip>

#include "CommandParse.hpp"
#include "Users.hpp"
#include "Channels.hpp"

#define BLACK	"\033[0;30m"
#define RED		"\033[0;31m"
#define GREEN	"\033[0;32m"
#define YELLOW	"\033[0;33m"
#define BLUE	"\033[0;34m"
#define PURPLE	"\033[0;35m"
#define CYAN	"\x1b[0;36m"
#define WHITE	"\033[0;37m"


class Server
{
private:
	bool						stopServer;
	std::string					_servername;
	int							_port;
	std::string					_password;
	int							_listener;	// // Listening socket descriptor 
	int							_newFd;		// Newly accept()ed socket descriptor
	struct	sockaddr_storage	_remoteaddr; // Client address
	socklen_t					_addrlen;
	char						_buf[512];    // Buffer for client data
	// char						remoteIP[INET6_ADDRSTRLEN];
	
	int							_fdCount;
	std::vector<struct pollfd>	clientSockets;
	std::vector<Users>			_Users;
	std::vector<Channels>		_Channels;
	// nick and user is pre new User vars, when push_back() new user then set this vars and clear it;
	
	CommandParse				cmdParse;

public:
	void			terminateServer();
	std::string		getPassword() const;
	Server(int port, std::string password);
	int				get_listener_socket(void);
	void			checkStatusAndThrow(int exitCode, std::string msg) throw(std::runtime_error);
	void			setUpPoll();
	struct pollfd	createPollStruct(int fd, short events);

	void			run();
	void			add_to_pollfds();
	void			*get_in_addr(struct sockaddr *sa);
	void			changeSocketOpt() throw(std::runtime_error);
	void			makeFdNonBlock(int fd) throw(std::runtime_error);
	void			bindSocket() throw(std::runtime_error);
	void			listenToSocket() throw(std::runtime_error);
	void			del_from_pollfds(int fd);
	void			NewConnection(void);
	void			ExistingConnection(int indexFd);
	bool			requestFromServerToAuthonticate(int newUserFd);
	void			ft_parse(int fd, std::string cmd) throw(std::runtime_error);
	void			ft_print_users() const;
	void			ft_print_Channels_Users();
	void			ft_show_auth_usage(int fd) throw(std::runtime_error);
	void			showGeneralGuide(int fd) throw(std::runtime_error);
	void			removeUserFromVector(int fd);
	void			removeAllUsersFromVector();
	void			closeAllUserFds();
	void			updateNickFromVector(int fd, std::string new_nick);

	std::string		getNickFromUsers(int fd) const;
	
	void			setIsOperWithFd(bool val, int fd);

	bool			checkUserInChannel(std::string chan, int fd);
	bool			checkChannelExistInChannelList(std::string chan);
	std::string		getUserBufferWithFd(std::vector<Users> _Users, int fd);
	void			setUserBufferWithFd(std::vector<Users> _Users, int fd);
	~Server();
};

#endif