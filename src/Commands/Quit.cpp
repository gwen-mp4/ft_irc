/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 10:57:48 by gwen              #+#    #+#             */
/*   Updated: 2026/06/09 10:57:49 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void Server::_handleQuit(Client *client, const std::vector<std::string> &params) {
    std::string reason = "";

    if (!params.empty()) {
        reason = params.at(0);

        if (reason[0] != ':') {
            this->sendClientMessage(client->getClientFd(), RED ":ircserv " ERR_NEEDMOREPARAMS " * :Not enough parameters\r\n" RES);
            return;
        }
        else if (reason[0] == ':')
            reason = reason.substr(1);
    }
    int fd = client->getClientFd();
    this->clearClient(fd, reason);
    //std::cout << "Quit handler called\n";
}
