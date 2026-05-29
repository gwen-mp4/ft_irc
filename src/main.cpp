/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 11:51:34 by gwen              #+#    #+#             */
/*   Updated: 2026/05/29 15:30:12 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Include.hpp"

int	parsePort( std::string portInput )
{
	int port = stoi(portInput);

	if (port < 0 || port > PORT_MAX)
		return -1;

	return port;
}

int	main(int ac, char **av) {
	if (ac != 3)
		return std::cerr << "Usage: ./ircserv <port> <password>\n", 1;
	try {
		if (parsePort(av[1]) != -1)
		{
			Server	srv;
			srv.run();
		}
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return 0;
}
