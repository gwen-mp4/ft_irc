/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 11:52:08 by gwen              #+#    #+#             */
/*   Updated: 2026/06/02 09:55:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Include.hpp"
    
Server::Server( const int& port, const std::string& password) :
    _port(port), 
    _socket(-1),
    _signal(false),
    _clientNb(0),
    _servPassword(password) {
    
    _cmds["NICK"] = &Server::_handleNick;
    _cmds["PASS"] = &Server::_handlePass;
    _cmds["USER"] = &Server::_handleUser;
    _cmds["OPER"] = &Server::_handleOper;
    _cmds["MODE"] = &Server::_handleMode;
    _cmds["QUIT"] = &Server::_handleQuit;
    _cmds["JOIN"] = &Server::_handleJoin;
    _cmds["PART"] = &Server::_handlePart;
    _cmds["TOPIC"] = &Server::_handleTopic;
    _cmds["KICK"] = &Server::_handleKick;
    _cmds["PRIVMSG"] = &Server::_handlePrivMsg;
    _cmds["NOTICE"] = &Server::_handleNotice;
}

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

// Send a message to client with the code (defined in ServerCodeIRC.hpp)
void    Server::sendClientMessage(int clientFD, std::string message) {
    
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
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    char buffer[80];
    int on = 1, clientSocket = -1, len = 1;
    int compres_array = 0;
    int close_conn;
    int reServSock = setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(this->_port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (struct sockaddr*)&serverAddress,
         sizeof(serverAddress));

    reServSock = listen(serverSocket, 32);

    struct pollfd fds[200];
    int nfds = 1, current_size = 0;
    fds[0].fd = serverSocket;
    fds[0].events = POLLIN;

    do {
        std::cout << "Waiting on poll()..." << std::endl;
        reServSock = poll(fds, nfds, 180000);

        if (reServSock == 0)
        {
            std::cout << "poll() time out. End program." << std::endl;
            break;
        }

        current_size = nfds;
        for (int i = 0; i < current_size; i++)
        {
            if (fds[i].revents == 0)
                continue;
            if (fds[i].revents != POLLIN)
            {
                std::cerr << "Error! revents = " << fds[i].revents << std::endl;
                this->_signal = true;
                break;
            }
            if (fds[i].fd == serverSocket)
            {
                std::cout << "Listening socket is readable." << std::endl;

                do {
                    clientSocket = accept(serverSocket, NULL, NULL);
                    if (clientSocket < 0)
                    {
                        if (errno != EWOULDBLOCK)
                        {
                          //perror("  accept() failed");
                          this->_signal = true;
                        }
                        break;
                    }

                    std::cout << "New incoming connection - " << clientSocket << std::endl;
                    fds[nfds].fd = clientSocket;
                    fds[nfds].events = POLLIN;
                    nfds++;
                } while (clientSocket != -1);
            }
            else
            {
                std::cout << "Descriptor " << fds[i]. fd << " is readable" << std::endl;
                close_conn = 0;

                do {
                    reServSock = recv(fds[i].fd, buffer, sizeof(buffer), 0);
                    if (reServSock < 0)
                    {
                        if (errno != EWOULDBLOCK)
                        {
                            //perror("  recv() failed");
                            close_conn = 1;
                        }
                        break;
                    }
                    if (reServSock == 0)
                    {
                        std::cout << "Connection closed" << std::endl;
                        close_conn = 1;
                        break;
                    }
                    len = reServSock;
                    std::cout << len << " bytes recieved" << std::endl;
                    
                    reServSock = send(fds[i].fd, buffer, len, 0);
                    if (reServSock < 0)
                    {
                        //perror("send() failed");
                        close_conn = 1;
                        break;
                    }
                } while (true);
                if (close_conn)
                {
                    close (fds[i].fd);
                    fds[i].fd = -1;
                    compres_array = 1;
                }
            }
        }
        if (compres_array)
        {
            compres_array = 0;
            for (int i = 0; i < nfds; i++)
            {
                if (fds[i].fd == -1)
                {
                    for (int j = i; j < nfds - 1; j++)
                    {
                        fds[j].fd = fds[j + 1].fd;
                    }
                    i--;
                    nfds--;
                }
            }
        }
    } while (this->_signal == false);

    for (int i = 0; i < nfds; i++)
    {
        if (fds[i].fd >= 0)
            close (fds[i].fd);
    }

    // int clientSocket
    //     = accept(serverSocket, NULL, NULL);

    // char buffer[1024] = { 0 };
    // recv(clientSocket, buffer, sizeof(buffer), 0);
    // std::cout << "Message from client: " << buffer
    //           << std::endl;

    // close(serverSocket);

    // while (true)
    // {
        
    // }
}