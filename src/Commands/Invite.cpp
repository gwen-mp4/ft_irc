#include "../../inc/Server.hpp"

void Server::_handleInvite(Client *client, const std::vector<std::string> &params) {
    (void) client;
    (void) params;
    std::cout << "Invite handler called\n";
}
