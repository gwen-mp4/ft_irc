#include "../../inc/Server.hpp"

void Server::_handleQuit(Client *client, const std::vector<std::string> &params) {
    std::string reason = "";

    if (!params.empty()) {
        reason = params.at(0);

        if (reason[0] != ':') {
            this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_NEEDMOREPARAMS " * :Not enough parameters\r\n" RES);
            return;
        }
        else if (reason[0] == ':')
            reason = reason.substr(1);
    }
    int fd = client->getClientFd();
    this->clearClient(fd, reason);
    //std::cout << "Quit handler called\n";
}
