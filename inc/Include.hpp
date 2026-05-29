/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Include.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 11:59:07 by gwen              #+#    #+#             */
/*   Updated: 2026/05/29 15:28:39 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_HPP
#define INCLUDE_HPP

#include <iostream>
#include <vector>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>
#include <csignal>
#include <exception>

#include "Channel.hpp"
#include "Client.hpp"
#include "Server.hpp"

#ifndef PORT_MAX
# define PORT_MAX 65535
#endif

#endif
