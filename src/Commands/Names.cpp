#include "../../inc/Server.hpp"

void Server::_handleNames(Client *client, const std::vector<std::string> &params) {
    
    (void)params;

    std::map<int, Client*>::iterator it = this->_clients.begin();
    for (; it != this->_clients.end(); ++it) {
        this->sendClientMessage(client->getClientFd(), it->second->getNickname() + "\r\n");
    }
}