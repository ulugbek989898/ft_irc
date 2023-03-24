/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:48:33 by uisroilo          #+#    #+#             */
/*   Updated: 2023/03/24 08:26:36 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/InitialParse.hpp"
#include "includes/Server.hpp"

int	main(int argc, char **argv) {
	try
	{
		InitialParse	objParse(argc, argv);
		Server			objServer(objParse.getPort(), objParse.getPassword());
		objServer.run();
		
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
}