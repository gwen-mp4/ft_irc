/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Notice.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 10:58:24 by gwen              #+#    #+#             */
/*   Updated: 2026/06/09 10:58:25 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void Server::_handleNotice(Client *client, const std::vector<std::string> &params) {
    
    if (params.size() < 2) {
        this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_NEEDMOREPARAMS " * :Not enough parameters\r\n" RES);
        return ;        
    }

    std::string target = params.at(0);

    std::string msg = BBLU "Notice from " + client->getNickname() + ": ";
    for (size_t i = 1; i < params.size(); ++i)
    {
        msg += params.at(i);
        if (i + 1 < params.size())
            msg += " ";
    }
    msg += RES "\r\n";

    if (this->_channels.count(target) > 0)
    {
        Channel *chan = this->_channels.at(target);
        chan->broadcastToChannel(client, msg, *this);
        return ;
    }
    else
    {
        if (this->_clientsNick.count(target) > 0)
        {
            sendClientMessage(this->_clientsNick.at(target)->getClientFd(), msg);
            return ;
        }
        else
        {
            this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_NOSUCHNICK " " + target + " * :No such nick/channel\r\n" RES);
            return ;
        }
    }
}
