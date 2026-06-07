#include "../../inc/Server.hpp"

void Server::_handleMode(Client *client, const std::vector<std::string> &params) {
    (void)client;
    (void)params;
    std::cout << "Mode handler called\n";
}
