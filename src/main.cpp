/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 11:51:34 by gwen              #+#    #+#             */
/*   Updated: 2026/05/29 15:19:28 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Include.hpp"

int	mian(int ac, char **av) {
	if (ac != 3)
		return std::cerr << "Usage: ./ircserv <port> <password>\n", 1;
	try {
		//parsing
		Server	srv;
		srv.run();
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return 0;
}
