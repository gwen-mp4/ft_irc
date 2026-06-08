/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 12:41:23 by storck            #+#    #+#             */
/*   Updated: 2026/06/05 11:42:17 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Include.hpp"

Channel::Channel(std::string name) :
    _name(name),
    _inviteOnly(false),
    _topicRestr(false),
    _limit(0),
    _password(""),
    _topic(""),
    _nbOp(0) {}

Channel::Channel( Channel const & other )
{
    *this = other;
}

Channel& Channel::operator=( Channel const & other )
{
    if (this != &other)
    {
        this->_name = other._name;
        this->_inviteOnly = other._inviteOnly;
        this->_topicRestr = other._topicRestr;
        this->_limit = other._limit;
        this->_password = other._password;
        this->_topic = other._topic;
        this->_nbOp = other._nbOp;
    }
    return (*this);
}

Channel::~Channel( void ) {}


/* ---------- Getter ---------- */

std::string Channel::getName() const {
    return _name;
}

bool        Channel::getInviteMode( void ) const
{
    return this->_inviteOnly;
}

bool        Channel::getTopicRestr( void ) const
{
    return this->_topicRestr;
}

int         Channel::getLimit( void ) const
{
    return this->_limit;
}

std::string Channel::getPassword( void ) const
{
    return this->_password;
}

std::string Channel::getTopic( void ) const
{
    return this->_topic;
}

std::map<int, Client*>  Channel::getOperators() const {
    return _operators;
}

std::map<int, Client*>  Channel::getMembers() const {
    return _members;
}

std::map<int, Client*>&  Channel::getOperators() {
    return _operators;
}

std::map<int, Client*>&  Channel::getMembers() {
    return _members;
}

bool    Channel::hasClient(Client* client) const {
    if (!client)
        return false;
    std::map<int, Client*>::const_iterator    it = _members.find(client->getClientFd());
    return (it != _members.end());
}

/* ---------- Setter ---------- */

void    Channel::setInviteMode( bool mod )
{
    this->_inviteOnly = mod;
}

void    Channel::setTopicRestr( bool res )
{
    this->_topicRestr = res;
}

void    Channel::setLimit( unsigned int lim )
{
    this->_limit = lim;
    setMode('l');
}

void    Channel::setPassword( std::string newPassW )
{
    this->_password = newPassW;
    setMode('k');
}

void    Channel::setTopic( std::string newTopic )
{
    this->_topic = newTopic;
}

void    Channel::setOperatorPrivileges(Client* oper, bool status) {
    if (status)
        this->addOperators(oper);
    else
        this->removeOperators(oper);
}

void    Channel::setMode(char mode) {
    _modes.insert(mode);
}

void    Channel::unsetLimit() {
    _limit = 0;
    unsetMode('l');
}

void    Channel::unsetPassword() {
    _password.clear();
    unsetMode('k');
}

void    Channel::unsetMode(char mode)  {
    _modes.erase(mode);
}


bool    Channel::hasMode(char mode) const {
    return _modes.find(mode) != _modes.end();
}

bool    Channel::isAlreadyInChannel(Client* client) const {
    return _members.find(client->getClientFd()) != _members.end();
}

bool    Channel::isInvited(Client* client) const {
    return _invitedClients.find(client) != _invitedClients.end();
}

bool Channel::isOperator(Client *client) const {
    return _operators.find(client->getClientFd()) != _operators.end();
}

bool Channel::isMember(Client *client) const {
    return _members.find(client->getClientFd()) != _members.end();
}

bool Channel::isFull() const {
    return this->hasMode('l') && static_cast<unsigned int>(_members.size()) >= _limit;
}

bool Channel::isEmpty() const {
    return _members.empty();
}

bool Channel::isPasswordProtected() const {
    return !_password.empty();
}

bool Channel::isTopicRestricted() const {
    return _topicRestr;
}

void    Channel::addOperators(Client* newOper) {
    _operators[newOper->getClientFd()] = newOper;
}

void    Channel::addMembers(Client* newMember) {
    _members[newMember->getClientFd()] = newMember;
}

void    Channel::removeOperators(Client* oper) {
    _operators.erase(oper->getClientFd());
}

void    Channel::removeMembers(Client* member, Server& server) {
    _members.erase(member->getClientFd());
    if (this->isOperator(member))
        this->removeOperators(member);
    if (this->isEmpty()) {
        server.deleteChannel(this->_name);
    }
}

void    Channel::inviteClient(Client* client) {
    _invitedClients.insert(client);
}

void    Channel::uninviteClient(Client* client) {
    _invitedClients.erase(client);
}

//Does not check if sender is member of the channel, it just broadcasts to all members except sender if sender is not NULL
void    Channel::broadcastToChannel(Client* sender, std::string message, Server& server) {
    std::map<int, Client*>::iterator it = _members.begin();
    for (; it != _members.end(); ++it) {
        if (sender == NULL || it->second->getClientFd() != sender->getClientFd())
            server.sendClientMessage(it->first, message);
    }
}
