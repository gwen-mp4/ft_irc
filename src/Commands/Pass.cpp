#include "../../inc/Server.hpp"

void Server::_handlePass(Client *client, const std::vector<std::string> &params) {

    // If client already sent valid password, send error 462
    if (client->hasSentPass()) {
        this->sendClientMessage(client->getClientFd(), YELLOW ":ircserv " ERR_ALREADYREGISTRED " * :You may not reregister\r\n" RES);
        return ;
    }

    // If number of parameters is <2, send error 461
    if (params.size() < 1) {
        this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_NEEDMOREPARAMS " * :Not enough parameters\r\n" RES);
        return ;
    }

    // Check password, if not valid, send error 464
    std::string password = params.at(0);
    if (password != Server::_servPassword) {
        this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_PASSWDMISMATCH " * :Password incorrect\r\n" RES);
        this->clearClient(client->getClientFd(), "");
        return ;
    }
    client->setSentPass(true);

    // If client is now registered, send welcome message
    if (client->isRegistered() && !client->isAlreadyRegistered()) {
        this->sendWelcomeMessage(client);
        client->setIsAlreadyRegistered(true);
    }
}
