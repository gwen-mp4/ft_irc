/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 11:51:59 by gwen              #+#    #+#             */
/*   Updated: 2026/05/29 13:16:09 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Include.hpp"

Client::Client( void ) {}

Client::Client( std::string name )
{
    this->_username = name;
}

Client::Client( Client const & other )
{
    *this = other;
}

Client& Client::operator=( Client const & other )
{
    if (this != &other)
    {
        this->_clientFd = other._clientFd;
        this->_clientIPadd = other._clientIPadd;
        this->_nickname = other._nickname;
        this->_username = other._username;
    }
    return (*this);
}

Client::~Client( void ) {}


/* ---------- Getter ---------- */

std::string Client::getUsername( void ) const
{
    return this->_username;
}

std::string Client::getNickname( void ) const
{
    return this->_nickname;
}

std::string Client::getclientIP( void ) const
{
    return this->_clientIPadd;
}

int         Client::getClientFd( void ) const
{
    return this->_clientFd;
}


/* ---------- Setter ---------- */

void    Client::setUsername( std::string username )
{
    this->_username = username;
}

void    Client::setNickname( std::string nickname )
{
    this->_nickname = nickname;
}

void    Client::setclientIP( std::string clientIP )
{
    this->_clientIPadd = clientIP;
}

void    Client::setClientFd( int fd )
{
    this->_clientFd = fd;
}
