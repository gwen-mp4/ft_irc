#include "../../inc/Server.hpp"

void Server::_handleMode(Client *client, const std::vector<std::string> &params) {
    if (params.size() < 2) {
        this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_NEEDMOREPARAMS " * :Not enough parameters\r\n" RES);
        return ;           
    }

    std::string channelName = params.at(0);
    if (_channels.find(channelName) == _channels.end()) {
        this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_NOSUCHCHANNEL " " + channelName + " * :No such channel\r\n" RES);
        return ;            
    }
    Channel*    channel = _channels[channelName];

    if (params.size() == 1) {
        std::string mode = "+";
        std::string modeParams = "";
        
        if (channel->hasMode('i')) mode += "i";
        if (channel->hasMode('p')) mode += "p";
        if (channel->hasMode('t')) mode += "t";
        if (channel->hasMode('k')) {
            mode += "k";
            modeParams += " " + channel->getPassword();
        }
        if (channel->hasMode('l')) {
            mode += "l";
            std::ostringstream  oss;
            oss << channel->getLimit();
            modeParams += " " + oss.str();
        }
        std::string channelModeMsg = BBLU ":ircserv " RPL_CHANNELMODEIS " " + client->getNickname() + " " + channel->getName()
            + " " + mode + modeParams + "\r\n" RES;
        this->sendClientMessage(client->getClientFd(), channelModeMsg);
    }

    std::cout << "Mode handler called\n";
}
