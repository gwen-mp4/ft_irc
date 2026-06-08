#include "../../inc/Server.hpp"

void Server::_handleInvite(Client *client, const std::vector<std::string> &params) {
    
    if (params.size() < 2) {
        this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_NEEDMOREPARAMS " * :Not enough parameters\r\n" RES);
        return ;        
    }

    std::string target_nick = params.at(0);
    std::string chan_name = params.at(1);
    Client  *target;
    Channel *chan;

    if (this->_clientsNick.count(target_nick) == 0)
    {
        this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_NOSUCHNICK " " + target_nick + " * :No such nickname\r\n" RES);
        return ;
    }
    else
        target = this->_clientsNick.at(target_nick);

    if (this->_channels.count(chan_name) == 0)
    {
        this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_NOSUCHCHANNEL " " + chan_name + " * :No such channel\r\n" RES);
        return ;
    }
    else
        chan = this->_channels.at(chan_name);

    if (chan->getMembers().count(target->getClientFd()) != 0)
    {
        this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_USERONCHANNEL " " + target_nick + " " + chan_name + " * :is already on taht channel \r\n" RES);
        return ;
    }
    
    if (chan->getInviteMode() == false)
    {
        this->sendClientMessage(client->getClientFd(), RED ":ircserv " + chan_name + " * :Is not in Invite mode.\r\n" RES);
        return ;
    }

    chan->inviteClient(target);
    this->sendClientMessage(target->getClientFd(), ":ircserv " + client->getNickname() + " invited you to channel " + chan_name + "\r\n");
    return ;
}
