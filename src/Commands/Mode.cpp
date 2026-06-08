#include "../../inc/Server.hpp"

void Server::_handleMode(Client *client, const std::vector<std::string> &params) {
    if (params.size() < 1) {
        this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_NEEDMOREPARAMS " * :Not enough parameters\r\n" RES);
        return ;           
    }

    std::string channelName = params.at(0);
    if (_channels.find(channelName) == _channels.end()) {
        this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_NOSUCHCHANNEL " " + channelName + " * :No such channel\r\n" RES);
        return ;            
    }
    Channel*    channel = _channels[channelName];

    // If command is "mode #channel", send channel's mode with code 324
    if (params.size() == 1) {
        std::string mode = "+";
        std::string modeParams = "";
        
        if (channel->hasMode('i')) mode += "i";
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
        std::string channelModeMsg = BBLU ":ircserv " RPL_CHANNELMODEIS " " + client->getNickname() + " " + channel->getName() + RES;
        if (!mode.empty() && !modeParams.empty())
            channelModeMsg += BLUE " " + mode + modeParams + RES;
        channelModeMsg += "\r\n";
        this->sendClientMessage(client->getClientFd(), channelModeMsg);
        return ;
    }

    if (!channel->isOperator(client)) {
        this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_CHANOPRIVSNEEDED " " + client->getNickname() + " "
            + channel->getName() + " * :You're not channel operator\r\n" RES);
        return ;
    }

    std::string modeStr = params.at(1);
    size_t  paramIndex = 2;
    bool    adding = true;

    for (size_t i = 0; i < modeStr.length(); ++i) {
        char    modeChar = modeStr.at(i);

        if (modeChar == '+')
            adding = true;
        else if (modeChar == '-')
            adding = false;
        else if (modeChar == 't' || modeChar == 'i') {
            if (adding)
                channel->setMode(modeChar);
            else
                channel->unsetMode(modeChar);
        }
        else if (modeChar == 'k') {
            if (adding) {
                if (params.size() <= paramIndex) {
                    this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_NEEDMOREPARAMS " * :Not enough parameters\r\n" RES);
                    return ;
                }
                std::string password = params.at(paramIndex++);
                channel->setPassword(password);
            }
            else
                channel->unsetPassword();
        }
        else if (modeChar == 'l') {
            if (adding) {
                if (params.size() <= paramIndex) {
                    this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_NEEDMOREPARAMS " * :Not enough parameters\r\n" RES);
                    return ;
                }
                std::istringstream  iss(params.at(paramIndex++));
                unsigned int    limit;
                if (!(iss >> limit)) {
                    this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_UNKNOWNMODE " * :Unknown mode char\r\n" RES);
                     return ;
                }
                channel->setLimit(limit);
            } else
                channel->unsetLimit();
        }
        else if (modeChar == 'o') {
            if (params.size() <= paramIndex) {
                this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_NEEDMOREPARAMS " * :Not enough parameters\r\n" RES);
                return ;
            }
            std::string nick = params.at(paramIndex++);
            Client* targetClient = NULL;
            if (this->_clientsNick.count(nick) == 0) {
                this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_NOSUCHNICK " " + nick + " * :No such nickname\r\n" RES);
                return;
            }
            targetClient = this->_clientsNick.at(nick);
            if (!channel->hasClient(targetClient)) {
                this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_USERNOTINCHANNEL " " + nick
                    + " " + channel->getName() + " * :They aren't on that channel\r\n" RES);
                return ;
            }
            if (adding)
                channel->setOperatorPrivileges(targetClient, true);
            else
                channel->setOperatorPrivileges(targetClient, false);
        }
        else {
            this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_UNKNOWNMODE " * :Unknown mode char\r\n" RES);
            return ;
        }
    }

    if (!channel->isEmpty()) {
        std::string modeChangeMsg = BBLU ":" + client->getNickname() + " MODE " + channel->getName() + " " + modeStr + RES;
        for (size_t i = 2; i < paramIndex; ++i)
            modeChangeMsg += BLUE " " + params.at(i) + RES;
        modeChangeMsg += "\r\n";
        channel->broadcastToChannel(client, modeChangeMsg, *this);
    }

    std::cout << "Mode handler called\n";
}
