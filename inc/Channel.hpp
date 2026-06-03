/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 12:41:05 by storck            #+#    #+#             */
/*   Updated: 2026/06/01 10:44:15 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "Include.hpp"

class Client;

class Channel
{
    private:
        bool                    _inviteOnly;
        bool                    _topicRestr;
        bool                    _userLimited;
        unsigned int            _limit;
        std::string             _password;
        std::string             _topic;
        unsigned int            _nbOp;
        std::map<int, Client*>    _operators; // Using map for optimization with an int (FD) and pointer to Client
        std::map<int, Client*>  _members; // Members of a channel using their FD

    public:
        Channel( void ); // To change with something else with constructor with parameters instead of default constructor
        Channel( Channel const & other );
        Channel& operator=( Channel const & other );
        ~Channel( void );

        // For now, we don't need it or won't need it for later
        // //Getter:
        // bool        getInviteMode( void ) const;
        // bool        getTopicRestr( void ) const;
        // bool        getUserLimited( void ) const;
        // int         getLimit( void ) const;
        // std::string getPassword( void ) const;
        // std::string getTopic( void ) const;
        std::map<int, Client*>  getMembers() const;

        // //Setter
        // void    setInviteMode( bool mod );
        // void    setTopicRestr( bool res );
        // void    setUserLimited( bool lim );
        // void    setLimit( int lim );
        // void    setPassword( std::string newPassW );
        // void    setTpoic( std::string newTopic );

        //void    Channel::broadcastToChannel(Client* sender, std::string message);
};

#endif