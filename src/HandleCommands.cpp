#include "../inc/Server.hpp"

void    Server::treatCommand(Client* client, const Command& msg) {
    if (msg.getCommandUpcase() != "PASS" && msg.getCommandUpcase() != "NICK" && msg.getCommandUpcase() != "USER" && !client->isRegistered()) {
        this->sendClientMessage(client->getClientFd(), ":server " ERR_NOTREGISTERED " * :You have not registered\r\n");
        return ;
    }

    // Temporary if/else, later change to pointer to pointer function
    if (msg.getCommand() == "PASS") this->_handlePass(client, msg.getParams());
    else if (msg.getCommandUpcase() == "NICK") this->_handleNick(client, msg.getParams());
    else if (msg.getCommandUpcase() == "USER") this->_handleUser(client, msg.getParams());
    else if (msg.getCommandUpcase() == "PRIVMSG") this->_handlePrivMsg(client, msg.getParams());
    else if (msg.getCommandUpcase() == "JOIN") this->_handleJoin(client, msg.getParams());
    else {
        this->sendClientMessage(client->getClientFd(), ":server " ERR_UNKNOWNCOMMAND " * " + msg.getCommand() + " :Unknown command\r\n");
    }
}
