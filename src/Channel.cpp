/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 12:41:23 by storck            #+#    #+#             */
/*   Updated: 2026/05/29 16:45:16 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Include.hpp"

Channel::Channel( void ) :
    _inviteOnly(false),
    _topicRestr(false),
    _userLimited(false),
    _limit(0),
    _password(NULL),
    _topic(NULL),
    _nbOp(0) {}
    //_operators(NULL) {}

Channel::Channel( Channel const & other )
{
    *this = other;
}

Channel& Channel::operator=( Channel const & other )
{
    if (this != &other)
    {
        this->_inviteOnly = other._inviteOnly;
        this->_topicRestr = other._topicRestr;
        this->_userLimited = other._userLimited;
        this->_limit = other._limit;
        this->_password = other._password;
        this->_topic = other._topic;
        this->_nbOp = other._nbOp;
        for (unsigned int i = 0; i < other._nbOp; ++i)
        {
            this->_operators.push_back(other._operators[i]);
        }
    }
    return (*this);
}

Channel::~Channel( void )
{
    for (unsigned int i = 0; i < this->_nbOp; ++i)
    {
        delete this->_operators[i];
    }
}


/* ---------- Getter ---------- */

bool        Channel::getInviteMode( void ) const
{
    return this->_inviteOnly;
}

bool        Channel::getTopicRestr( void ) const
{
    return this->_topicRestr;
}

bool        Channel::getUserLimited( void ) const
{
    return this->_userLimited;
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


/* ---------- Setter ---------- */

void    Channel::setInviteMode( bool mod )
{
    this->_inviteOnly = mod;
}

void    Channel::setTopicRestr( bool res )
{
    this->_topicRestr = res;
}

void    Channel::setUserLimited( bool lim )
{
    this->_userLimited = lim;
}

void    Channel::setLimit( int lim )
{
    this->_limit = lim;
}

void    Channel::setPassword( std::string newPassW )
{
    this->_password = newPassW;
}

void    Channel::setTpoic( std::string newTopic )
{
    this->_topic = newTopic;
}
