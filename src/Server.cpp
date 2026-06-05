/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 11:52:08 by gwen              #+#    #+#             */
/*   Updated: 2026/06/05 12:14:15 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Include.hpp"
    
Server::Server( const int& port, const std::string& password) :
    _port(port), 
    _socket(-1),
    _clientNb(1),
    _servPassword(password),
    _version(1.0) {

    _cmds["NICK"] = &Server::_handleNick;
    _cmds["PASS"] = &Server::_handlePass;
    _cmds["USER"] = &Server::_handleUser;
    //_cmds["OPER"] = &Server::_handleOper;
    //_cmds["MODE"] = &Server::_handleMode;
    _cmds["QUIT"] = &Server::_handleQuit;
    _cmds["JOIN"] = &Server::_handleJoin;
    //_cmds["PART"] = &Server::_handlePart;
    //_cmds["TOPIC"] = &Server::_handleTopic;
    _cmds["KICK"] = &Server::_handleKick;
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
        this->_channels = other._channels;
        this->_version = other._version;
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

char*    Server::getDate( void ) const {
    time_t  currentTime = time(NULL);
    time(&currentTime);
    char *time_str = ctime(&currentTime);
    time_str[std::strcspn(time_str, "\r\n")] = '\0';
    return time_str;
}

void    Server::sendWelcomeMessage(Client* client) const {
    std::string welcomeMsg = GREEN ":ircserv " RPL_WELCOME " :Welcome to the Internet Relay Network "
        + client->getNickname() + '!' + client->getUsername() + '@' + client->getHostname() + "\r\n" RES;
    std::string welcomeMsg2 = GREEN ":ircserv " RPL_YOURHOST " :Your host is "
        + client->getServerName() + ", running version " + ft_itoa(this->_version) + "\r\n" RES;
    std::string welcomeMsg3 = GREEN ":ircserv " RPL_CREATED " :This server was created on "
        + std::string(this->getDate()) + "\r\n" RES;
    std::string welcomeMsg4 = GREEN ":ircserv " RPL_MYINFO " " + client->getServerName() + " " + ft_itoa(this->_version)
        + " iow tkoli\r\n" RES;
    sendClientMessage(client->getClientFd(), welcomeMsg);
    sendClientMessage(client->getClientFd(), welcomeMsg2);
    sendClientMessage(client->getClientFd(), welcomeMsg3);
    sendClientMessage(client->getClientFd(), welcomeMsg4);
}

// // Send a message to client with the code (defined in ServerCodeIRC.hpp)
void    Server::sendClientMessage(int clientFD, std::string message) const
{
    if (send(clientFD, message.c_str(), message.size(), 0) == -1)
        std::cerr << "send() failed." << std::endl;
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

bool Server::_signal = false;
void Server::signalHandler( int sig )
{
	std::cout << std::endl << "Signal " << sig << " Received!" << std::endl;
	Server::_signal = true;
}

void Server::newClient( void )
{
    Client              *cl = new Client();
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

    cl->setClientFd(inFd);
    cl->setClientIP(inet_ntoa(clientAddr.sin_addr));
    //this->_clients[this->_clients.size()] = &cl;
    this->_clients.insert(std::pair<int, Client*>(inFd, cl));
    this->_fds[this->_clientNb] = newPoll;
    this->_clientNb++;

    std::cout << GREEN "Client <" << inFd << "> connected" << RES << std::endl;
}

void    Server::clearBuff( void )
{
    for (int i = 0; i < BUFF_SIZE; i++)
    {
        this->_buffer[i] = 0;
    }
}

void    Server::clearClient( int fd )
{
    this->_clientsNick.erase(this->_clients[fd]->getNickname());
    this->_clients[fd]->setSentPass(false);
    this->_clients[fd]->setSentNick(false);
    this->_clients[fd]->setSentUser(false);
    this->_clients[fd]->setNickname("");
    //this->_clients[fd]->setIsOperator(false);
    delete this->_clients[fd];
    this->_clients.erase(fd);
}

void    Server::clientInput( int fd )
{
    clearBuff();

    ssize_t bytes = recv(fd, this->_buffer, sizeof(this->_buffer) - 1, 0);

    if (bytes <= 0)
    {
        std::cerr << RED "Client <" << fd << "> disconnected" << RES << std::endl;
        clearClient(fd);
        this->_clientNb--;
        close(fd);
    }
    else
    {

        this->_buffer[bytes] = '\0';
        std::cout << GREEN "Client <" << fd << "> input: " << this->_buffer << RES;
        treatCommand(this->_clients[fd], this->_buffer);
        //sendClientMessage(fd, this->_buffer);
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