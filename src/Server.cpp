/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 11:52:08 by gwen              #+#    #+#             */
/*   Updated: 2026/06/08 10:25:10 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Include.hpp"
    
Server::Server( const int& port, const std::string& password) :
    _port(port), 
    _socket(-1),
    _clientNb(1),
    _servPassword(password),
    _version(1.0),
    _creationTime(getCreationDate()) {

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

Server::~Server( void )
{
    for (std::map<int, Client*>::iterator it = this->_clients.begin(); it != this->_clients.end(); ++it) {
        if (it->second) {
            close(it->second->getClientFd());
            delete it->second;
        }
    }
    _clients.clear();
    for (std::map<std::string, Channel*>::iterator it = this->_channels.begin(); it != this->_channels.end(); ++it) {
        if (it->second) {
            delete it->second;
        }
    }
    _channels.clear();
}

char*    Server::getCreationDate( void ) const {
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
        + std::string(this->_creationTime) + "\r\n" RES;
    std::string welcomeMsg4 = GREEN ":ircserv " RPL_MYINFO " " + client->getServerName() + " " + ft_itoa(this->_version)
        + " iow tkoli\r\n" RES;
    sendClientMessage(client->getClientFd(), welcomeMsg);
    sendClientMessage(client->getClientFd(), welcomeMsg2);
    sendClientMessage(client->getClientFd(), welcomeMsg3);
    sendClientMessage(client->getClientFd(), welcomeMsg4);
}

void    Server::sendWelcomeToChannelMessage(Client* client, Channel* chan) const {
    std::string topicMsg;
    if (chan->getTopic().empty()) {
        topicMsg = GREEN ":ircserv " RPL_NOTOPIC " " + client->getNickname() + " " + chan->getName() + " :No topic is set\r\n" RES;
    }
    else {
        topicMsg = GREEN ":ircserv " RPL_TOPIC " " + chan->getName() + " :" + chan->getTopic() + "\r\n" RES;
    }
    sendClientMessage(client->getClientFd(), topicMsg);
    const std::map<int, Client*>& members = chan->getMembers();
    std::string namesMsg = GREEN ":ircserv " RPL_NAMREPLY " = " + chan->getName() + " :";
    for (std::map<int, Client*>::const_iterator it = members.begin(); it != members.end(); ++it) {
        if (it->second->isOperator()) {
            namesMsg += '@';
        }
        namesMsg += it->second->getNickname() + ' ';
    }
    namesMsg += "\r\n";
    sendClientMessage(client->getClientFd(), namesMsg);
    std::string endNamesMsg = GREEN ":ircserv " RPL_ENDOFNAMES " " + chan->getName() + " :End of NAMES list\r\n" RES;
    sendClientMessage(client->getClientFd(), endNamesMsg);
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

void    Server::deleteChannel(const std::string& chan_name) {
    std::map<std::string, Channel*>::iterator it = this->_channels.find(chan_name);
    if (it != this->_channels.end()) {
        delete it->second;
        this->_channels.erase(it);
    }
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
    //this->_fds[this->_clientNb] = newPoll;
    this->_fds.push_back(newPoll);
    this->_clientNb++;

    std::cout << GREEN "Client <" << inFd << "> connected" << RES << std::endl;
}

void    Server::clearBuff( void )
{
    for (int i = 0; i < BUFF_SIZE; ++i)
    {
        this->_buffer[i] = 0;
    }
}

void    Server::clearClient( int fd, std::string reason )
{
    std::map<int, Client*>::iterator cit = this->_clients.find(fd);
    if (cit == this->_clients.end())
        return;
    Client *client = cit->second;

    // Build quit message
    std::string quitMsg;
    if (!reason.empty()) {
        quitMsg = BYEL ":" + client->getNickname() + " QUIT :" + reason + "\r\n" RES;
    } else {
        quitMsg = BYEL ":" + client->getNickname() + " QUIT :Client quit\r\n" RES;
    }

    // Remove client from all joined channels and notify them
    std::set<Channel*> channels = client->getJoinedChannels();
    for (std::set<Channel*>::iterator it = channels.begin(); it != channels.end(); ++it) {
        Channel *chan = *it;
        chan->broadcastToChannel(client, quitMsg, *this);
        // Erase by fd from channel maps
        std::map<int, Client*>& members = chan->getMembers();
        std::map<int, Client*>& ops = chan->getOperators();
        members.erase(fd);
        ops.erase(fd);
        // If channel empty, delete it from server
        if (members.empty()) {
            std::map<std::string, Channel*>::iterator chit = this->_channels.find(chan->getName());
            if (chit != this->_channels.end()) {
                delete chit->second;
                this->_channels.erase(chit);
            }
        }
    }

    // Remove from nickname map if present
    if (!client->getNickname().empty())
        this->_clientsNick.erase(client->getNickname());

    // delete client and erase from map
    delete client;
    this->_clients.erase(cit);
    close(fd);
    for (size_t i = 0; i < this->_fds.size(); i++){
        if (this->_fds[i].fd == fd) {
            this->_fds.erase(this->_fds.begin() + i);
            break;
        }
    }
    if (this->_clientNb > 0)
        this->_clientNb--;
}

void    Server::clientInput( int fd )
{
    clearBuff();

    ssize_t bytes = recv(fd, this->_buffer, sizeof(this->_buffer) - 1, 0);

    if (bytes <= 0) {
        std::cerr << RED "Client <" << fd << "> disconnected" << RES << std::endl;
        clearClient(fd, "");
    } else {
        this->_buffer[bytes] = '\0';
        std::cout << GREEN "Client <" << fd << "> input: " << this->_buffer << RES;
        treatCommand(this->_clients[fd], this->_buffer);
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

    if (bind(this->_socket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0)
    {
        std::cout << RED << "Port is already in use." << RES << std::endl;
        close(this->_socket);
        return ;
    }

    reServSock = listen(this->_socket, 32);

    struct pollfd   newCli;

    newCli.fd = this->_socket;
	newCli.events = POLLIN;
	newCli.revents = 0;
	this->_fds.push_back(newCli);

    // this->_fds[0].fd = this->_socket;
    // this->_fds[0].events = POLLIN;

    do {
        signal(SIGINT, Server::signalHandler);
		signal(SIGQUIT, Server::signalHandler);
        std::cout << "Waiting on poll()..." << std::endl;
        reServSock = poll(&_fds[0], _fds.size(), -1);

        if (reServSock == -1) {
            if (Server::_signal)
                break;
            throw(std::runtime_error("poll() failed"));
        }

        for (unsigned int i = 0; i < this->_fds.size(); ++i)
        {
            if (this->_signal == false && (this->_fds[i].revents & POLLIN))
            {
                if (this->_fds[i].fd == this->_socket)
                    newClient();
                else
                    clientInput(this->_fds[i].fd);
            }
        }
    } while (this->_signal == false);

    std::cout << "CLOSING SERVER." << std::endl;

    // Close all client connections cleanly
    for (size_t i = 0; i < this->_fds.size(); )
    {
        int fd = this->_fds[i].fd;
        if (fd == this->_socket) {
            ++i;
            continue;
        }
        // clearClient will remove client from maps and delete client
        this->clearClient(fd, "Server shutting down");
        // do not increment i because we erased current element
    }
    if (this->_socket >= 0)
    {
        std::cout << "CLOSING SERVER SOCKET." << std::endl;
        close(this->_socket);
        this->_socket = -1;
    }
    this->_fds.clear();
    this->_clientNb = 0;
}