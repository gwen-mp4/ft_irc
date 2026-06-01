/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 11:52:08 by gwen              #+#    #+#             */
/*   Updated: 2026/06/01 10:55:31 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Include.hpp"
    
Server::Server( const int& port, const std::string& password) :
    _port(port), 
    _socket(-1),
    _signal(false),
    _clientNb(0),
    _servPassword(password) {}

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
        this->_clients = other._clients;
    }
    return (*this);
}

Server::~Server( void )
{
    // Don't need to delete because a container frees itself when destructor is called
    // for (unsigned int i = 0; i < this->_clientNb; ++i)
    // {
    //     delete this->_clients[i];
    // }
}


// /* ---------- Getter ---------- */

// int Server::getport(void) const
// {
//     return this->_port;
// }

// int Server::getSocket(void) const
// {
//     return this->_socket;
// }

// bool Server::getSignal(void) const
// {
//     return this->_signal;
// }

// Client *Server::getClient(int index) const
// {
//     return this->_clients[index];
// }

// std::string Server::getServPassword( void ) const
// {
//     return this->_servPassword;
// }


// /* ---------- Setter ---------- */

// void    Server::setport( int por )
// {
//     this->_port = por;
// }

// void    Server::setSocket( int soc )
// {
//     this->_socket = soc;
// }

// void    Server::setSignal( bool sig )
// {
//     this->_signal = sig;
// }

// void    Server::setServPassword( std::string pswd )
// {
//     this->_servPassword = pswd;
// }


void    Server::run( void )
{
    std::cout << "Running Server" << std::endl;

    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(this->_port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (struct sockaddr*)&serverAddress,
         sizeof(serverAddress));

    listen(serverSocket, 5);

    int clientSocket
        = accept(serverSocket, NULL, NULL);

    char buffer[1024] = { 0 };
    recv(clientSocket, buffer, sizeof(buffer), 0);
    std::cout << "Message from client: " << buffer
              << std::endl;

    close(serverSocket);
    std::cout << "Closing Server" << std::endl;

    // while (true)
    // {
        
    // }
}