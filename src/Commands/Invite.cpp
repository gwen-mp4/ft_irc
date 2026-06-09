/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 11:05:26 by gwen              #+#    #+#             */
/*   Updated: 2026/06/09 11:05:27 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void Server::_handleInvite(Client *client, const std::vector<std::string> &params) {
    
    if (params.size() < 2) {
        this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_NEEDMOREPARAMS " * :Not enough parameters\r\n" RES);
        return ;        
    }

    std::string target_nick = params.at(0);
    std::string chan_name = params.at(1);
    Client  *target = NULL;
    Channel *chan = NULL;

    if (this->_clientsNick.count(target_nick) == 0)
    {
        this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_NOSUCHNICK " " + target_nick + " * :No such nickname\r\n" RES);
        return ;
    }
    else
        target = this->_clientsNick.at(target_nick);

    if (this->_channels.count(chan_name) == 0)
    {
        this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_NOSUCHCHANNEL " " + chan_name
            + " * :No such channel\r\n" RES);
        return ;
    }
    else
        chan = this->_channels.at(chan_name);

    if (chan->getMembers().count(target->getClientFd()) != 0)
    {
        this->sendClientMessage(client->getClientFd(), YELLOW ":ircserv " ERR_USERONCHANNEL " "
            + target_nick + " " + chan_name + " * :is already on channel \r\n" RES);
        return ;
    }
    
    chan->inviteClient(target);
    this->sendClientMessage(target->getClientFd(), BLUE ":" + client->getNickname() + " INVITE "
        + target_nick + " :" + chan_name + "\r\n" RES);
    this->sendClientMessage(client->getClientFd(), BLUE ":ircserv " RPL_INVITING " "
        + client->getNickname() + " " + target_nick + " :" + chan_name + "\r\n" RES);
}
