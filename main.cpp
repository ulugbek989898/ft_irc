/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:48:33 by uisroilo          #+#    #+#             */
/*   Updated: 2023/03/23 16:19:13 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/InitialParse.hpp"

int	main(int argc, char **argv) {
	try
	{
		InitialParse	objParse(argc, argv);
		
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
}