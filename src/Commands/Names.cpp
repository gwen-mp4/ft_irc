#include "../../inc/Server.hpp"

void Server::_handleNames(Client *client, const std::vector<std::string> &params) {
    (void) client;
    (void) params;
    std::cout << "Names handler called\n";
}