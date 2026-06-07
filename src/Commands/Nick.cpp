#include "../../inc/Server.hpp"

bool    Server::validNickname(const std::string& nickname) const {

    // This norms follows the norms given by GeekShed IRC Network
    if (nickname.empty() || nickname.length() > 30)
        return false;
    std::string specialChar = "[]{}\\|^`–_";
    if (!std::isalpha(nickname[0]) && specialChar.find(nickname[0]) == std::string::npos)
        return false;
    for (size_t i = 1; i < nickname.length(); ++i) {
        char    c = nickname.at(i);
        if (!std::isalnum(c) && specialChar.find(c) == std::string::npos)
            return false;
    }
    return true;
}

void Server::_handleNick(Client *client, const std::vector<std::string> &params) {

    // If number of parameters is <1, that means no nickname were given
    // So send error 431
    if (params.size() < 1) {
        this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_NONICKNAMEGIVEN " * :No nickname given\r\n" RES);
        return ;
    }

    if (params.size() > 1) {
        this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_ERRONEUSNICKNAME " Client<" + ft_itoa(client->getClientFd())
           + "> :Erroneus nickname\r\n" RES);
        return ;
    }

    // Take the new nickname and verify if it respects the IRC norms, otherwise, send error 432
    std::string nickname = params.at(0);
    if (!validNickname(nickname)) {
        this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_ERRONEUSNICKNAME " Client<" + ft_itoa(client->getClientFd())
           + "> " + nickname + " :Erroneus nickname\r\n" RES);
        return ;
    }

    // Check if nickname is already used by another user, otherwise, send error 433
    std::map<std::string, Client*>::iterator nickIt = _clientsNick.find(nickname);
    if (nickIt != _clientsNick.end() && nickIt->second != client) {
        this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_NICKNAMEINUSE " " + nickname + " :Nickname is already in use\r\n" RES);
        return ;
    }

    // Remove the old nickname mapping if this client already had one
    std::string oldNickname = client->getNickname();
    if (!oldNickname.empty()) {
        std::map<std::string, Client*>::iterator oldIt = _clientsNick.find(oldNickname);
        if (oldIt != _clientsNick.end() && oldIt->second == client)
            _clientsNick.erase(oldIt);
    }

    // Store the new nickname for this client
    _clientsNick[nickname] = client;
    
    // If client is already registered and wants to change nickname, inform all clients of the modification
    // It doens't seems to work, even if the client is registered and in joined channels probably, it doesn't send the message to the other clients, I don't know why
    if (client->isRegistered() && client->isAlreadyRegistered()) {
        const std::set<Channel*>& channels = client->getJoinedChannels();
        std::cout << "Passed\n";
        if (!channels.empty()) {
            std::cout << "Passed joined channels\n";
            std::string msg = BBLU ":" + oldNickname + " NICK :" + nickname + "\r\n" RES;
            for (std::set<Channel*>::iterator it = channels.begin(); it != channels.end(); ++it) {
                (*it)->broadcastToChannel(client, msg, *this);
                std::cout << "Passed broadcast\n";
                if (*it == NULL)
                    std::cout << "Joined channel is NULL\n";
            }
        }
    }

    client->setNickname(nickname);
    if (!client->isRegistered())
        client->setSentNick(true);

    // If client is now registered, send welcome message
    if (client->isRegistered() && !client->isAlreadyRegistered()) {
        this->sendWelcomeMessage(client);
        client->setIsAlreadyRegistered(true);
    }
}
