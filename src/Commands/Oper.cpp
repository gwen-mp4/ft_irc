#include "../../inc/Server.hpp"

void Server::_handleOper(Client *client, const std::vector<std::string> &params) {
    (void) client;
    (void) params;
    std::cout << "Oper handler called\n";
}
