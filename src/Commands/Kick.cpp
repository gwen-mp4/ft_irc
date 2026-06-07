#include "../../inc/Server.hpp"

void Server::_handleKick(Client *client, const std::vector<std::string> &params) {
    if (params.size() < 2) {
        this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_NEEDMOREPARAMS " * :Not enough parameters\r\n" RES);
        return ;        
    }

    std::string chan_name = params.at(0);
    Channel     *chan;

    // try {
    //     chan = this->_channels.at(chan_name);
    // }
    // catch(const std::out_of_range& e) {
    //     this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_NOSUCHCHANNEL + chan_name + " * :No such channel\r\n" RES);
    //     return ;
    // }
    if (this->_channels.count(chan_name) == 0)
    {
        this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_NOSUCHCHANNEL + chan_name + " * :No such channel\r\n" RES);
        return ;
    }
    chan = this->_channels.at(chan_name);

    if (!(chan->getOperators()[client->getClientFd()]))
    {
        this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_NOSUCHCHANNEL + client->getNickname() + " " + chan_name + " * :You're not channel operator\r\n" RES);
        return ;
    }

    std::string victim_name = params.at(1);
    Client      *victim;

    // try {
    //     victim = this->_clientsNick[victim_name];
    // }
    // catch(const std::out_of_range& e) {
    //     this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_NOSUCHNICK + victim_name + " * :No such nickname\r\n" RES);
    //     return ;
    // }
    if (this->_clientsNick.count(victim_name) == 0)
    {
        this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_NOSUCHNICK + victim_name + " * :No such nickname\r\n" RES);
        return ;
    }
    victim = this->_clientsNick.at(victim_name);

    if (!(chan->getMembers()[victim->getClientFd()]))
    {
        this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_USERNOTINCHANNEL + victim->getNickname() + " " + chan_name + " * :They aren't on that channel\r\n" RES);
        return ;
    }

    chan->getMembers().erase(victim->getClientFd());
    victim->getJoinedChannels().erase(chan);

    //std::cout << "Kick handler called\n";
}
