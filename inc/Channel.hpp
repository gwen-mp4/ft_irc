/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 12:41:05 by storck            #+#    #+#             */
/*   Updated: 2026/06/05 11:41:46 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "Include.hpp"

class Client;
class Server;

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
        std::map<int, Client*>  _operators; // Using map for optimization with an int (FD) and pointer to Client
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
        std::map<int, Client*>  getOperators() const;
        std::map<int, Client*>  getMembers() const;

        //void    addMember(Client* client);
        //void    removeMember(Client* client);

        // //Setter
        // void    setInviteMode( bool mod );
        // void    setTopicRestr( bool res );
        // void    setUserLimited( bool lim );
        // void    setLimit( int lim );
        // void    setPassword( std::string newPassW );
        // void    setTpoic( std::string newTopic );

        void    addOperators(Client* newOper);
        void    addMembers(Client* newMember);
        void    removeOperators(Client* oper);
        void    removeMembers(Client* member);

        void    broadcastToChannel(Client* sender, std::string message, Server& server);
};

#endif