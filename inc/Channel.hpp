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
        std::string             _name;
        bool                    _inviteOnly;
        bool                    _topicRestr;
        bool                    _userLimited;
        unsigned int            _limit;
        std::string             _password;
        std::string             _topic;
        unsigned int            _nbOp;
        std::map<int, Client*>  _operators; // Using map for optimization with an int (FD) and pointer to Client
        std::map<int, Client*>  _members; // Members of a channel using their FD
        std::set<Client*>  _invitedClients; // Set of invited clients to the channel

    public:
        Channel( std::string name ); // To change with something else with constructor with parameters instead of default constructor
        Channel( Channel const & other );
        Channel& operator=( Channel const & other );
        ~Channel( void );

        //Getter:
        std::string getName() const;
        bool        getInviteMode( void ) const;
        bool        getTopicRestr( void ) const;
        bool        getUserLimited( void ) const;
        int         getLimit( void ) const;
        std::string getPassword( void ) const;
        std::string getTopic( void ) const;
        std::map<int, Client*>  getOperators() const;
        std::map<int, Client*>  getMembers() const;

        //Setter
        void    setInviteMode( bool mod ); // +i or -i
        void    setTopicRestr( bool res ); // +t or -t
        void    setUserLimited( bool lim ); // +l or -l
        void    setLimit( int lim ); // +l or -l
        void    setPassword( std::string newPassW ); // +k or -k
        void    setTopic( std::string newTopic ); // TOPIC command
        void    setOperatorPrivileges(Client* oper, bool status); // +o or -o

        bool    hasMode(std::string mode) const;
        bool    isAlreadyInChannel(Client* client) const;
        bool    isInvited(Client* client) const;
        bool    isOperator(Client* client) const;
        bool    isMember(Client* client) const;
        bool    isFull() const;
        bool    isEmpty() const;
        bool    isPasswordProtected() const;
        bool    isTopicRestricted() const;

        void    addOperators(Client* newOper);
        void    addMembers(Client* newMember);
        void    removeOperators(Client* oper);
        void    removeMembers(Client* member, Server& server);
        void    inviteClient(Client* client);
        void    uninviteClient(Client* client);

        void    broadcastToChannel(Client* sender, std::string message, Server& server);
};

#endif