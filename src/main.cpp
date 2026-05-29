/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 11:51:34 by gwen              #+#    #+#             */
/*   Updated: 2026/05/29 16:19:13 by gwen             ###   ########.fr       */
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
		Server	srv(port, av[2]);
		srv.run();
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return 0;
}
