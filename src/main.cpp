/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 11:51:34 by gwen              #+#    #+#             */
/*   Updated: 2026/05/29 15:45:13 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Include.hpp"

int	parsePort( std::string portInput )
{
	std::istringstream	iss(portInput);
	int	portValue;
	if (iss >> portValue) {
		if (portValue < 0 || portValue > PORT_MAX)
		std::runtime_error("wrong port");
	}
	else
		std::runtime_error("input string stream error");
	return portValue;
}

int	main(int ac, char **av) {
	if (ac != 3)
		return std::cerr << "Usage: ./ircserv <port> <password>\n", 1;
	try {
		parsePort(av[1]);
		Server	srv;
		srv.run();
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return 0;
}
