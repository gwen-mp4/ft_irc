#include "../inc/Server.hpp"

void    Server::treatCommand(Client* client, std::string raw_line) {
    Command msg(raw_line); // Parse the raw command into a Command object
    
    if (msg.getCommandUpcase() != "PASS" && msg.getCommandUpcase() != "NICK" && msg.getCommandUpcase() != "USER" && !client->isRegistered()) {
        std::cout << "Client not registered, cannot execute command: " << msg.getCommand() << std::endl;
        //this->sendClientMessage(client->getClientFd(), ":server " ERR_NOTREGISTERED " * :You have not registered\r\n");
        return ;
    }

    // Temporary if/else, later change to pointer to pointer function
    if (msg.getCommand() == "PASS") this->_handlePass(client, msg.getParams());
    else if (msg.getCommandUpcase() == "NICK") this->_handleNick(client, msg.getParams());
    else if (msg.getCommandUpcase() == "USER") this->_handleUser(client, msg.getParams());
    else if (msg.getCommandUpcase() == "PRIVMSG") this->_handlePrivMsg(client, msg.getParams());
    else if (msg.getCommandUpcase() == "JOIN") this->_handleJoin(client, msg.getParams());
    else {
        std::cout << "Unknown command: " << msg.getCommand() << std::endl;
        //this->sendClientMessage(client->getClientFd(), ":server " ERR_UNKNOWNCOMMAND " * " + msg.getCommand() + " :Unknown command\r\n");
    }
}

void Server::_handleNick(Client *client, const std::vector<std::string> &params) {
    (void) client;
    (void) params;
    std::cout << "Nick handler called\n";
}

void Server::_handlePass(Client *client, const std::vector<std::string> &params) {
    (void) client;
    (void) params;
    std::cout << "Pass handler called\n";
}

void Server::_handleUser(Client *client, const std::vector<std::string> &params) {
    (void) client;
    (void) params;
    std::cout << "User handler called\n";
}

// void Server::_handleOper(Client *client, const std::vector<std::string> &params) {

// }

// void Server::_handleMode(Client *client, const std::vector<std::string> &params) {

// }

// void Server::_handleQuit(Client *client, const std::vector<std::string> &params) {

// }

void Server::_handleJoin(Client *client, const std::vector<std::string> &params) {
    (void) client;
    (void) params;
    std::cout << "Join handler called\n";
}

// void Server::_handlePart(Client *client, const std::vector<std::string> &params) {

// }

// void Server::_handleTopic(Client *client, const std::vector<std::string> &params) {

// }

// void Server::_handleKick(Client *client, const std::vector<std::string> &params) {

// }

void Server::_handlePrivMsg(Client *client, const std::vector<std::string> &params) {
    (void) client;
    (void) params;
    std::cout << "Private message handler called\n";
}

// void Server::_handleNotice(Client *client, const std::vector<std::string> &params) {

// }
