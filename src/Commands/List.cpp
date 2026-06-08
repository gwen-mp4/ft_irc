#include "../../inc/Server.hpp"

void Server::_handleList(Client *client, const std::vector<std::string> &params) {
    
    (void)params;

    std::map<std::string, Channel*>::iterator it = this->_channels.begin();
    for (; it != this->_channels.end(); ++it) {
        this->sendClientMessage(client->getClientFd(), it->second->getName() + "\r\n");
    }
}