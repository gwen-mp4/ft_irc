#include "../../inc/Server.hpp"

void Server::_handlePrivMsg(Client *client, const std::vector<std::string> &params) {
    
    if (params.size() < 2) {
        this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_NEEDMOREPARAMS " * :Not enough parameters\r\n" RES);
        return ;        
    }

    std::string target = params.at(0);

    std::string msg = BLUE + client->getNickname() + " says: ";
    for (long unsigned int i = 1; i < params.size(); i++)
    {
        msg = msg + " " + params.at(i);
    }
    msg = msg + RES + "\r\n";

    if (this->_channels.count(target) > 0)
    {
        Channel *chan = this->_channels.at(target);
        for (size_t i = 0; i < chan->getMembers().size(); i++)
        {
            sendClientMessage(chan->getMembers()[i]->getClientFd(), msg);
        }
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
