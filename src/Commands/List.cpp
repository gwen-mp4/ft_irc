/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 10:59:02 by gwen              #+#    #+#             */
/*   Updated: 2026/06/09 10:59:03 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void Server::_handleList(Client *client, const std::vector<std::string> &params) {
    
    (void)params;

    std::map<std::string, Channel*>::iterator it = this->_channels.begin();
    for (; it != this->_channels.end(); ++it) {
        this->sendClientMessage(client->getClientFd(), it->second->getName() + "\r\n");
    }
}