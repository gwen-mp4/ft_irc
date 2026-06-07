#include "../../inc/Server.hpp"

void Server::_handlePart(Client *client, const std::vector<std::string> &params) {
    if (params.size() < 1) {
        this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_NEEDMOREPARAMS " * :Not enough parameters\r\n" RES);
        return ;        
    }

    std::string chan_name = params.at(0);

    std::vector<std::string> chan_list = this->ft_split<std::vector<std::string> >(chan_name, ',');

    for (std::vector<std::string>::iterator it = chan_list.begin(); it != chan_list.end(); ++it) {
        std::string name = *it;
        if (name.empty() || (name[0] != '#' && name[0] != '&')) {
            this->sendClientMessage(client->getClientFd(), std::string(RED ":ircserv " ERR_NOSUCHCHANNEL) + " " + name + " * :No such channel\r\n" RES);
            continue;
        }
        if (_channels.find(name) == _channels.end()) {
            this->sendClientMessage(client->getClientFd(), std::string(RED ":ircserv " ERR_NOSUCHCHANNEL) + " " + name + " * :No such channel\r\n" RES);
            continue;
        }

        Channel*    channel = this->_channels[name];

        // Check if client is in channel, otherwise send error code 442
        if (!channel->hasClient(client)) {
            this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_NOTONCHANNEL " " + client->getNickname()
                + " " + chan_name + " * :You're not on that channel\r\n" RES);
            continue ;
        }
        if (!channel->isEmpty()) {
            std::string joinMsg = YELLOW ":" + client->getNickname() + " PART " + name + "\r\n" RES;
            channel->broadcastToChannel(client, joinMsg, *this);
        }

        // Remove member from channel, it automatically removes operator too if needed and delete channel if empty
        channel->removeMembers(client, *this);
        client->removeChannel(channel);
    }
    //std::cout << "Part handler called\n";
}
