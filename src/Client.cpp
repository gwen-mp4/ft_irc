/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 11:51:59 by gwen              #+#    #+#             */
/*   Updated: 2026/06/01 10:43:52 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Include.hpp"

Client::Client( void ) :
    _username(NULL),
    _nickname(NULL),
    _clientIpAddr(NULL),
    _clientFd(-1) {}

Client::Client( const std::string& name, const std::string& nick ) : _username(name), _nickname(nick) {}

Client::Client( Client const & other )
{
    *this = other;
}

Client& Client::operator=( Client const & other )
{
    if (this != &other)
    {
        this->_clientFd = other._clientFd;
        this->_clientIpAddr = other._clientIpAddr;
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
    return this->_clientIpAddr;
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
    this->_clientIpAddr = clientIP;
}

void    Client::setClientFd( int fd )
{
    this->_clientFd = fd;
}


void    Client::run( void )
{
    std::cout << "Running client" << std::endl;

    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    connect(clientSocket, (struct sockaddr*)&serverAddress,
            sizeof(serverAddress));

    const char* message = "Hello, server!";
    send(clientSocket, message, 14, 0);

    close(clientSocket);
    std::cout << "Closing client" << std::endl;
}
