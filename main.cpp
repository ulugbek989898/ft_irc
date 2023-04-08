/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:48:33 by uisroilo          #+#    #+#             */
/*   Updated: 2023/04/08 15:29:01 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/InitialParse.hpp"
#include "includes/CommandParse.hpp"
#include "includes/Server.hpp"
#include <signal.h>

static Server *getServerPtr(Server *saveMe) {
	static Server *savedPtr;
	return saveMe ? (savedPtr = saveMe) : savedPtr;
}

static void signalHandler(int sig) {
	(void)sig;
	// std::cout << "i am here\n";
	getServerPtr(NULL)->terminateServer();
}

int	main(int argc, char **argv) {

	signal(SIGINT, signalHandler);
	signal(SIGQUIT, signalHandler);
	try
	{
		InitialParse	objParse(argc, argv);
		Server			objServer(objParse.getPort(), objParse.getPassword());
		getServerPtr(&objServer);
		objServer.run();
		
	}
	catch(const std::exception& e)
	{
		//close(4);
		std::cerr << e.what() << '\n';
		return 1;
	}
}
