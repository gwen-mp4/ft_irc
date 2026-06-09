/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleCommands.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 11:07:05 by gwen              #+#    #+#             */
/*   Updated: 2026/06/09 11:07:05 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

void    Server::treatCommand(Client* client, std::string raw_line) {
    if (raw_line.empty() || raw_line.find_first_not_of(" \r\n") == std::string::npos)
        return ;

    Command msg; // Parse the raw command into a Command object
	msg.parseCmd(raw_line);

    if (msg.getCommandUpcase() == "QUIT") {
        _handleQuit(client, msg.getParams());
        return ;
    }
    
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
