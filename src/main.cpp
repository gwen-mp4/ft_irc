/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 11:51:34 by gwen              #+#    #+#             */
/*   Updated: 2026/06/01 10:46:09 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Include.hpp"

static int	parsePort( const std::string& portInput )
{
	std::istringstream	iss(portInput);
	int	portValue;
	if (iss >> portValue && iss.eof()) {
		if (portValue < 0 || portValue > PORT_MAX) {
			throw std::runtime_error("wrong port");
		}
	}
	else
		throw std::runtime_error("wrong port");
	return portValue;
}

int	main(int ac, char **av) {
	if (ac != 3)
		return std::cerr << "Usage: ./ircserv <port> <password>\n", 1;
	try {
		int	port = parsePort(av[1]);
		std::string password(av[2]);
		Server	srv(port, password);
		srv.run();
		Client clt("Name", "Nick");
		clt.run();
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return 0;
}
