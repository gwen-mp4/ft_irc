/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 11:52:08 by gwen              #+#    #+#             */
/*   Updated: 2026/06/03 17:34:33 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Include.hpp"
    
Server::Server( const int& port, const std::string& password) :
    _port(port), 
    _socket(-1),
    _clientNb(1),
    _servPassword(password) {
    
    _cmds["NICK"] = &Server::_handleNick;
    _cmds["PASS"] = &Server::_handlePass;
    _cmds["USER"] = &Server::_handleUser;
    //_cmds["OPER"] = &Server::_handleOper;
    //_cmds["MODE"] = &Server::_handleMode;
    //_cmds["QUIT"] = &Server::_handleQuit;
    _cmds["JOIN"] = &Server::_handleJoin;
    //_cmds["PART"] = &Server::_handlePart;
    //_cmds["TOPIC"] = &Server::_handleTopic;
    //_cmds["KICK"] = &Server::_handleKick;
    _cmds["PRIVMSG"] = &Server::_handlePrivMsg;
    //_cmds["NOTICE"] = &Server::_handleNotice;
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
        this->_socket = other._socket;
        this->_clients = other._clients;
        this->_clientsNick = other._clientsNick;
        this->_servPassword = other._servPassword;
        this->_cmds = other._cmds;
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

// // Send a message to client with the code (defined in ServerCodeIRC.hpp)
// void    Server::sendClientMessage(int clientFD, std::string message) {
    
// }


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

bool Server::_signal = false;
void Server::signalHandler( int sig )
{
	std::cout << std::endl << "Signal " << sig << " Received!" << std::endl;
	Server::_signal = true;
}

void Server::newClient( void )
{
    Client              cl;
    struct sockaddr_in  clientAddr;
    struct pollfd       newPoll;
    socklen_t           len = sizeof(clientAddr);

    int inFd = accept(this->_socket, (sockaddr*)&(clientAddr), &len);
    if (inFd == -1)
    {
        std::cerr << "accept() failed" << std::endl;
        return ;
    }
    if (fcntl(inFd, F_SETFL, O_NONBLOCK) == -1)
    {
        std::cerr << "fcntl() failed" << std::endl;
        return ;
    }
    
    newPoll.fd = inFd;
    newPoll.events = POLLIN;
    newPoll.revents = 0;

    cl.setClientFd(inFd);
    cl.setClientIP(inet_ntoa(clientAddr.sin_addr));
    //this->_clients[this->_clients.size()] = &cl;
    this->_clients.insert(std::pair<int, Client*>(inFd, &cl));
    this->_fds[this->_clientNb] = newPoll;
    this->_clientNb++;

    std::cout << "\033[31mClient <" << inFd << "> connected\033[m" << std::endl;
}

void    Server::clearBuff( void )
{
    for (int i = 0; i < 1024; i++)
    {
        this->_buffer[i] = 0;
    }
}

void    Server::clientInput( int fd )
{
    clearBuff();

    ssize_t bytes = recv(fd, this->_buffer, sizeof(this->_buffer) - 1, 0);

    if (bytes <= 0)
    {
        std::cerr << "\033[36mClient <" << fd << "> disconnected\033[m" << std::endl;
        // Clear client...
        this->_clientNb--;
        close(fd);
    }
    else
    {
        this->_buffer[bytes] = '\0';
        std::cout << "\033[32mClient <" << fd << "> input: " << this->_buffer << "\033[m";
        sendClientMessage(fd, this->_buffer);
    }
}

void    Server::run( void )
{
    this->_socket = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    int reServSock = setsockopt(this->_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt));

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(this->_port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    bind(this->_socket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    reServSock = listen(this->_socket, 32);

    this->_fds[0].fd = this->_socket;
    this->_fds[0].events = POLLIN;

    do {
        signal(SIGINT, Server::signalHandler);
		signal(SIGQUIT, Server::signalHandler);
        std::cout << "Waiting on poll()..." << std::endl;
        reServSock = poll(this->_fds, this->_clientNb, -1);

        if (reServSock == 0)
            throw(std::runtime_error("poll() failed"));

        for (unsigned int i = 0; i < this->_clientNb; i++)
        {
            if (this->_fds[i].revents & POLLIN)
            {
                if (this->_fds[i].fd == this->_socket)
                    newClient();
                else
                    clientInput(this->_fds[i].fd);
            }
        }
    } while (this->_signal == false);

    std::cout << "ClOSING SERVER." << std::endl;

    int nfds = this->_clientNb;
    for (int i = 0; i < nfds; i++)
    {
        if (this->_fds[i].fd >= 0)
        {
            close (this->_fds[i].fd);
            this->_clientNb--;
        }
    }
    if (reServSock != -1)
    {
        std::cout << "ClOSING SERVER." << std::endl;
        close(reServSock);
    }
}