/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 11:04:57 by gwen              #+#    #+#             */
/*   Updated: 2026/06/09 11:04:57 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void Server::_handleJoin(Client *client, const std::vector<std::string> &params) {

    if (params.size() < 1) {
        this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_NEEDMOREPARAMS " * :Not enough parameters\r\n" RES);
        return ;        
    }
    
    std::string chan_name = params.at(0);
    std::vector<std::string> chan_list = this->ft_split<std::vector<std::string> >(chan_name, ',');
    std::vector<std::string> key_list;
    if (params.size() > 1)
        key_list = this->ft_split<std::vector<std::string> >(params.at(1), ',');

    for (size_t idx = 0; idx < chan_list.size(); ++idx) {
        std::string name = chan_list.at(idx);
        std::string key = (idx < key_list.size() ? key_list.at(idx) : "");

        if (name.empty() || (name[0] != '#' && name[0] != '&')) {
            this->sendClientMessage(client->getClientFd(), std::string(RED ":ircserv " ERR_NOSUCHCHANNEL) + name + " * :No such channel\r\n" RES);
            continue;
        }
        Channel *chan = NULL;
        if (_channels.find(name) == _channels.end()) {
            chan = new Channel(name);
            _channels[name] = chan;
            chan->addOperators(client);
        } else {
            chan = _channels[name];
            if (chan->isAlreadyInChannel(client)) {
                this->sendClientMessage(client->getClientFd(), std::string(YELLOW ":ircserv " ERR_USERONCHANNEL) + " " + client->getNickname() + " "
                    + name + " * :You're already on that channel\r\n" RES);
                continue;
            }
            if (chan->hasMode('i') && !chan->isInvited(client)) {
                this->sendClientMessage(client->getClientFd(), std::string(RED ":ircserv " ERR_INVITEONLYCHAN) + " " + name + " * :Cannot join channel (+i)\r\n" RES);
                continue;
            }
            if (chan->hasMode('k')) {
                if (key.empty() || key != chan->getPassword()) {
                    this->sendClientMessage(client->getClientFd(), std::string(RED ":ircserv " ERR_BADCHANNELKEY) + " " + name + " * :Cannot join channel (+k)\r\n" RES);
                    continue;
                }
            }
            if (chan->isFull()) {
                this->sendClientMessage(client->getClientFd(), std::string(RED ":ircserv " ERR_CHANNELISFULL) + " " + name + " * :Cannot join channel (+l)\r\n" RES);
                continue;
            }
        }
        chan->addMembers(client);
        client->addChannel(chan);
        if (chan->isInvited(client))
            chan->uninviteClient(client);
        this->sendWelcomeToChannelMessage(client, chan);
        if (chan->isOperator(client))
            this->sendClientMessage(client->getClientFd(), std::string(BGRN ":ircserv " RPL_YOUREOPER) + " * :You are now an IRC operator\r\n" RES);
        if (!chan->isEmpty()) {
            std::string joinMsg = BLUE ":" + client->getNickname() + " JOIN " + name + "\r\n" RES;
            chan->broadcastToChannel(client, joinMsg, *this);
        }
    }
    
    // std::cout << "Join handler called\n";
}
