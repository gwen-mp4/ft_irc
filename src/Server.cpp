/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 11:52:08 by gwen              #+#    #+#             */
/*   Updated: 2026/05/29 15:19:42 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Include.hpp"

Server::Server( void ) {}

Server::Server( Server const & other )
{
    *this = other;
}

Server& Server::operator=( Server const & other )
{
    if (this != &other)
    {
        this->_port = other._port;
        this->_signal = other._signal;
        this->_socket = other._socket;
        for (int i = 0; i < other._clientNb; i++)
        {
            this->_clients.push_back(other._clients[i]);
        }
    }
    return (*this);
}

Server::~Server( void )
{
    for (int i = 0; i < this->_clientNb; i++)
    {
        delete this->_clients[i];
    }
}


/* ---------- Getter ---------- */

int     Server::getport( void ) const
{
    return this->_port;
}

int     Server::getSocket( void ) const
{
    return this->_socket;
}

bool    Server::getSignal( void ) const
{
    return this->_signal;
}

Client* Server::getClient( int index ) const
{
    return this->_clients[index];
}

std::string Server::getServPassword( void ) const
{
    return this->_servPassword;
}


/* ---------- Setter ---------- */

void    Server::setport( int por )
{
    this->_port = por;
}

void    Server::setSocket( int soc )
{
    this->_socket = soc;
}

void    Server::setSignal( bool sig )
{
    this->_signal = sig;
}

void    Server::setServPassword( std::string pswd )
{
    this->_servPassword = pswd;
}


void    Server::run( void )
{
    while (true)
    {
        
    }
}