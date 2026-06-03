/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 11:51:59 by gwen              #+#    #+#             */
/*   Updated: 2026/06/01 15:42:29 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Include.hpp"

Client::Client( const std::string& name, const std::string& nick ) : _username(name), _nickname(nick) {}

Client::Client( Client const & other )
{
    *this = other;
}

Client& Client::operator=( Client const & other )
{
    if (this != &other)
    {
        this->_clientFd = other._clientFd;
        this->_clientIpAddr = other._clientIpAddr;
        this->_nickname = other._nickname;
        this->_username = other._username;
    }
    return (*this);
}

Client::~Client( void ) {}


/* ---------- Getter ---------- */

std::string Client::getUsername( void ) const
{
    return this->_username;
}

std::string Client::getNickname( void ) const
{
    return this->_nickname;
}

std::string Client::getclientIP( void ) const
{
    return this->_clientIpAddr;
}

int         Client::getClientFd( void ) const
{
    return this->_clientFd;
}

std::set<Channel*>  Client::getJoinedChannels() const {
    return this->_joinedChannels;
}

bool Client::hasSentNick() const {
    return _hasGivenNick;
}

bool Client::hasSentPass() const {
    return _hasEnteredPass;
}

bool Client::hasSentUser() const {
    return _hasGivenUser;
}

bool    Client::isRegistered() const {
    return _isRegistered;
}


// /* ---------- Setter ---------- */

// void    Client::setUsername( std::string username )
// {
//     this->_username = username;
// }

// void    Client::setNickname( std::string nickname )
// {
//     this->_nickname = nickname;
// }

// void    Client::setclientIP( std::string clientIP )
// {
//     this->_clientIpAddr = clientIP;
// }

void    Client::setClientFd( const int& fd )
{
    this->_clientFd = fd;
}

void Client::setSentPass(bool status) {
    this->_hasEnteredPass = status;
}

void Client::setSentNick(bool status) {
    this->_hasGivenNick = status;
}

void Client::setSentUser(bool status) {
    this->_hasGivenUser = status;
}
