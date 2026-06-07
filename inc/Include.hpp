/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Include.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 11:59:07 by gwen              #+#    #+#             */
/*   Updated: 2026/06/04 11:17:49 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_HPP
# define INCLUDE_HPP

# include <sstream>
# include <string>
# include <iostream>
# include <vector>
# include <map>
# include <set>
# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>
# include <fcntl.h>
# include <unistd.h>
# include <arpa/inet.h>
# include <poll.h>
# include <csignal>
# include <exception>
# include <algorithm>
# include <bits/stdc++.h>
# include <ctime>

# include "Channel.hpp"
# include "Client.hpp"
# include "Server.hpp"
# include "Command.hpp"

# include "ServerCodeIRC.hpp"

# ifndef PORT_MAX
#  define PORT_MAX 65535
# endif

// # ifndef BUFF_SIZE
// #  define BUFF_SIZE 1024
// # endif

# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define BRED "\e[1;31m"
# define BGRN "\e[1;32m"
# define BYEL "\e[1;33m"
# define BBLU "\e[1;34m"
# define RES "\033[0m"

#endif
