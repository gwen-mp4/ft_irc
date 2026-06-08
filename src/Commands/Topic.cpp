#include "../../inc/Server.hpp"

void Server::_handleTopic(Client *client, const std::vector<std::string> &params) {
    
    if (params.size() < 1) {
        this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_NEEDMOREPARAMS " * :Not enough parameters\r\n" RES);
        return ;        
    }

    std::string chan_name = params.at(0);

    if (this->_channels.count(chan_name) == 0)
    {
        this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_NOSUCHCHANNEL + chan_name + " * :No such channel\r\n" RES);
        return ;
    }

    Channel *chan = this->_channels.at(chan_name);

    if (chan->getTopicRestr() == true)
    {
        if (chan->getOperators().count(client->getClientFd()) == 0)
        {
            this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_NOSUCHCHANNEL + client->getNickname() + " " + chan_name + " * :You're not channel operator\r\n" RES);
            return ;
        }
    }
    else if (chan->getMembers().count(client->getClientFd()) == 0)
    {
        this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_NOTONCHANNEL " " + client->getNickname()
            + " " + chan_name + " * :You're not on that channel\r\n" RES);
        return ;
    }
    else
    {
        std::string new_topic;
        if (params.size() > 1)
            new_topic = params.at(1);
        else
            new_topic = "";
        chan->setTopic(new_topic);
        this->sendClientMessage(client->getClientFd(), BLUE ":ircserv: channel " + chan_name + "\'s topic changed to: " + new_topic + "/r/n" RES);
        return;
    }
}
