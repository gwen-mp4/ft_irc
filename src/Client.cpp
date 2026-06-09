/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 11:51:59 by gwen              #+#    #+#             */
/*   Updated: 2026/06/09 10:42:16 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Include.hpp"

Client::Client( void ) :
    _username(""),
    _nickname(""),
    _realname(""),
    _serverName(""),
    _hostname(""),
    _clientIpAddr(""),
    _clientFd(-1),
    _hasEnteredPass(false),
    _hasGivenNick(false),
    _hasGivenUser(false),
    _isAlreadyRegistered(false),
    _cliBuff("") {}

Client::Client( Client const & other ) {
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
        this->_realname = other._realname;
        this->_hostname = other._hostname;
        this->_serverName = other._serverName;
        this->_hasGivenNick = other._hasGivenNick;
        this->_hasEnteredPass = other._hasEnteredPass;
        this->_hasGivenUser = other._hasGivenUser;
        this->_joinedChannels = other._joinedChannels;
        this->_isAlreadyRegistered = other._isAlreadyRegistered;
    }
    return (*this);
}

Client::~Client( void )
{
    std::cout << "Client " << this->_clientFd << " destroyed" << std::endl;
}

/* ---------- Getter ---------- */

std::string Client::getUsername( void ) const
{
    return this->_username;
}

std::string Client::getNickname( void ) const
{
    return this->_nickname;
}

std::string Client::getRealName() const {
    return this->_realname;
}

std::string Client::getHostname() const {
    return this->_hostname;
}

std::string Client::getServerName() const {
    return this->_serverName;
}

std::string Client::getclientIP( void ) const
{
    return this->_clientIpAddr;
}

int         Client::getClientFd( void ) const
{
    return this->_clientFd;
}

const std::set<Channel*>&  Client::getJoinedChannels() const {
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
    return _hasGivenNick && _hasEnteredPass && _hasGivenUser;
}

bool Client::isAlreadyRegistered() const {
    return _isAlreadyRegistered;
}

std::string Client::getCliBuff() const {
    return _cliBuff;
}

/* ---------- Setter ---------- */

void    Client::setUsername( const std::string& username )
{
    this->_username = username;
}

void    Client::setNickname( const std::string& nickname )
{
    this->_nickname = nickname;
}

void    Client::setRealName(const std::string &realname) {
    this->_realname = realname;
}

void    Client::setHostname(const std::string &hostname) {
    this->_hostname = hostname;
}

void    Client::setServerName(const std::string &servername) {
    this->_serverName = servername;
}

void    Client::setClientIP( const std::string& clientIP )
{
    this->_clientIpAddr = clientIP;
}

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

void Client::setIsAlreadyRegistered(bool status) {
    this->_isAlreadyRegistered = status;
}

void Client::setCliBuff(std::string buff) {
    this->_cliBuff = buff;
}

void    Client::addChannel(Channel* channel) {
    this->_joinedChannels.insert(channel);
}

void    Client::removeChannel(Channel* channel) {
    this->_joinedChannels.erase(channel);
}
