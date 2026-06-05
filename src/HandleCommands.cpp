#include "../inc/Server.hpp"

void    Server::treatCommand(Client* client, std::string raw_line) {
    if (raw_line.empty() || raw_line.find_first_not_of(" \r\n") == std::string::npos)
        return ;

    Command msg; // Parse the raw command into a Command object
	msg.parseCmd(raw_line);
    
    bool    isAuth = (msg.getCommandUpcase() == "PASS" || msg.getCommandUpcase() == "NICK" || msg.getCommandUpcase() == "USER");

    if (!client->isRegistered() && !isAuth) {
        this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_NOTREGISTERED " * :You have not registered\r\n" RES);
        return ;
    }

    // Function pointer to handle commands, if command is not found, send error 421
    if (_cmds.count(msg.getCommandUpcase())) {
        (this->*(_cmds[msg.getCommandUpcase()]))(client, msg.getParams());
        return ;
    }
    else {
        this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_UNKNOWNCOMMAND " * " + msg.getCommand() + " :Unknown command\r\n" RES);
        return ;
    }
}

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
    if (client->isRegistered()) {
        std::set<Channel*> channels = client->getJoinedChannels();
        if (!channels.empty()) {
            std::string msg = BLUE ":" + oldNickname + "NICK :" + nickname + "\r\n" RES;
            for (std::set<Channel*>::iterator it = channels.begin(); it != channels.end(); ++it) {
                (*it)->broadcastToChannel(client, msg, *this);
            }
        }
    }

    client->setNickname(nickname);
    if (!client->isRegistered())
        client->setSentNick(true);

    // If client is now registered, send welcome message
    if (client->isRegistered()) {
        this->sendWelcomeMessage(client);
    }
}

void Server::_handlePass(Client *client, const std::vector<std::string> &params) {

    // If client already sent valid password, send error 462
    if (client->hasSentPass()) {
        this->sendClientMessage(client->getClientFd(), YELLOW ":ircserv " ERR_ALREADYREGISTRED " * :You may not reregister\r\n" RES);
        return ;
    }

    // If number of parameters is <2, send error 461
    if (params.size() < 1) {
        this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_NEEDMOREPARAMS " * :Not enough parameters\r\n" RES);
        return ;
    }

    // Check password, if not valid, send error 464
    std::string password = params.at(0);
    if (password != Server::_servPassword) {
        this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_PASSWDMISMATCH " * :Password incorrect\r\n" RES);
        // Function to disconnect client
        return ;
    }
    client->setSentPass(true);

    // If client is now registered, send welcome message
    if (client->isRegistered()) {
        this->sendWelcomeMessage(client);
    }
}

bool    Server::validUsername(const std::string& username) const {
    if (username.empty() || username.length() > 10)
        return false;
    for (size_t i = 0; i < username.length(); ++i) {
        char    c = username.at(i);
        if (!std::isalnum(c) && c != '_' && c != '-')
            return false;
    }
    return true;
}

void Server::_handleUser(Client *client, const std::vector<std::string> &params) {

    // If client already sent USER command, send error 462
    if (client->hasSentUser()) {
        this->sendClientMessage(client->getClientFd(), YELLOW ":ircserv " ERR_ALREADYREGISTRED " * :You may not reregister\r\n" RES);
        return ;
    }

    // If number of parameters is <4, send error 461
    if (params.size() < 4) {
        this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_NEEDMOREPARAMS " * :Not enough parameters\r\n" RES);
        return ;        
    }

    std::string username = params.at(0);
    std::string hostname = params.at(1);
    std::string serverName = params.at(2);
    std::string realName = params.at(3);

    if (realName[0] != ':') {
        this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_NEEDMOREPARAMS " * :Not enough parameters\r\n" RES);
        return ;
    }
    else if (realName[0] == ':') {
        realName = realName.substr(1);
    }

    // Check if username is valid, otherwise, send error 461 (there's no real error code for this)
    if (!validUsername(username)) {
        this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_NEEDMOREPARAMS " Client <" + ft_itoa(client->getClientFd())
           + "> " + username + " :Not enough parameters\r\n" RES);
        return ;
    }

    if (hostname.empty())
        hostname = "unknown";
    
    client->setUsername(username);
    client->setHostname(hostname);
    client->setServerName(serverName);
    client->setRealName(realName);
    client->setSentUser(true);

    // If client is now registered, send welcome message
    if (client->isRegistered()) {
        this->sendWelcomeMessage(client);
    }
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

// int main() {
//     Server server(6667, "hi");
//     // 1. On crée un faux client avec un FD fictif
//     Client* fake_client = new Client("user", "nick");

//     std::cout << "--- TEST 1 : Inscription ---" << std::endl;
//     // On simule l'envoi de commandes successives par le client
//     server.treatCommand(fake_client, "pass password123");
//     server.treatCommand(fake_client, "NIck deaddpool");
//     server.treatCommand(fake_client, "USER guest 0 * :Mon Nom");

//     std::cout << "\n--- TEST 2 : Commande hors inscription ---" << std::endl;
//     // On simule un JOIN
//     server.treatCommand(fake_client, "JOIN #42");

//     delete fake_client;
//     return 0;
// }
