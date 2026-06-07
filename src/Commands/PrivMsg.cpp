#include "../../inc/Server.hpp"

void Server::_handlePrivMsg(Client *client, const std::vector<std::string> &params) {
    (void) client;
    (void) params;
    std::cout << "Private message handler called\n";
}
