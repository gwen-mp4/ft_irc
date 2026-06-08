#include "../../inc/Server.hpp"

void Server::_handleKick(Client *client, const std::vector<std::string> &params) {
    if (params.size() < 2) {
        this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_NEEDMOREPARAMS " * :Not enough parameters\r\n" RES);
        return ;        
    }

    std::string chan_name = params.at(0);
    std::string victim_name = params.at(1);

    // Optional params for reason
    std::string reason = client->getNickname();
    if (params.size() >= 3) {
        reason = params.at(2);
        if (reason.at(0) == ':')
            reason = reason.substr(1);
        else {
            for (size_t i = 2; i < params.size(); ++i) {
                reason += params.at(i);
                if (i + 1 < params.size())
                    reason += " ";
            }
        }
    }

    if (this->_channels.find(chan_name) == this->_channels.end()) {
        this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_NOSUCHCHANNEL " " + chan_name + " * :No such channel\r\n" RES);
        return ;      
    }

    Channel     *chan = _channels[chan_name];

    if (!chan->hasClient(client)) {
        this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_NOTONCHANNEL " " + client->getNickname() + " "
            + chan->getName() + " * :You're not on that channel\r\n" RES);
        return ;
    }
    if (!(chan->getOperators()[client->getClientFd()])) {
        this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_CHANOPRIVSNEEDED " " + client->getNickname() + " "
            + chan_name + " * :You're not channel operator\r\n" RES);
        return ;
    }

    Client      *victim = NULL;

    if (this->_clientsNick.count(victim_name) == 0) {
        this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_NOSUCHNICK + victim_name + " * :No such nickname\r\n" RES);
        return ;
    }
    victim = this->_clientsNick.at(victim_name);

    if (!chan->hasClient(victim)) {
        this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_USERNOTINCHANNEL " " + victim->getNickname()
            + " " + chan_name + " * :They aren't on that channel\r\n" RES);
        return ;
    }

    if (!chan->isEmpty()) {
        std::string kickMsg = BYEL ":" + client->getNickname() + " KICK " + chan->getName() + " " + victim->getNickname() + RES;
        if (params.size() >= 3) {
            kickMsg += YELLOW " :" + reason + RES;
        }
        kickMsg += "\r\n";
        chan->broadcastToChannel(client, kickMsg, *this);
    }

    chan->removeMembers(victim, *this);
    victim->removeChannel(chan);

    //std::cout << "Kick handler called\n";
}
