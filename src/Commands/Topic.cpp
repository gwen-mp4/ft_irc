#include "../../inc/Server.hpp"

void Server::_handleTopic(Client *client, const std::vector<std::string> &params) {
    (void) client;
    (void) params;
    std::cout << "Topic handler called\n";
}
