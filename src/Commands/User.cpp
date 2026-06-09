/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 10:57:23 by gwen              #+#    #+#             */
/*   Updated: 2026/06/09 10:57:25 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

bool    Server::validUsername(const std::string& username) const {
    if (username.empty() || username.length() > 10)
        return false;
    for (size_t i = 0; i < username.length(); ++i) {
        char    c = username.at(i);
        if (!std::isalnum(c) && c != '_' && c != '-')
            return false;
    }
    return true;
}

void Server::_handleUser(Client *client, const std::vector<std::string> &params) {

    // If client already sent USER command, send error 462
    if (client->hasSentUser()) {
        this->sendClientMessage(client->getClientFd(), YELLOW ":ircserv " ERR_ALREADYREGISTRED " * :You may not reregister\r\n" RES);
        return ;
    }

    // If number of parameters is <4, send error 461
    if (params.size() < 4) {
        this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_NEEDMOREPARAMS " * :Not enough parameters\r\n" RES);
        return ;        
    }

    std::string username = params.at(0);
    std::string hostname = params.at(1);
    std::string serverName = params.at(2);
    std::string realName = params.at(3);

    if (realName[0] != ':') {
        this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_NEEDMOREPARAMS " * :Not enough parameters\r\n" RES);
        return ;
    }
    else if (realName[0] == ':') {
        realName = realName.substr(1);
    }

    // Check if username is valid, otherwise, send error 461 (there's no real error code for this)
    if (!validUsername(username)) {
        this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_NEEDMOREPARAMS " Client <" + ft_itoa(client->getClientFd())
           + "> " + username + " :Not enough parameters\r\n" RES);
        return ;
    }

    if (hostname.empty())
        hostname = "unknown";
    
    client->setUsername(username);
    client->setHostname(hostname);
    client->setServerName(serverName);
    client->setRealName(realName);
    client->setSentUser(true);

    // If client is now registered, send welcome message
    if (client->isRegistered() && !client->isAlreadyRegistered()) {
        this->sendWelcomeMessage(client);
        client->setIsAlreadyRegistered(true);
    }
}
