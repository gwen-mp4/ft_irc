/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Names.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 10:58:52 by gwen              #+#    #+#             */
/*   Updated: 2026/06/09 10:58:53 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void Server::_handleNames(Client *client, const std::vector<std::string> &params) {
    
    (void)params;

    std::map<int, Client*>::iterator it = this->_clients.begin();
    for (; it != this->_clients.end(); ++it) {
        this->sendClientMessage(client->getClientFd(), it->second->getNickname() + "\r\n");
    }
}