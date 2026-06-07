#include "../../inc/Server.hpp"

void Server::_handleNotice(Client *client, const std::vector<std::string> &params) {
    (void) client;
    (void) params;
    std::cout << "Notice handler called\n";
}
