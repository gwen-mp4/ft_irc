/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 12:41:12 by storck            #+#    #+#             */
/*   Updated: 2026/06/09 10:37:09 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

# ifndef BUFF_SIZE
#  define BUFF_SIZE 1024
# endif

#include "Include.hpp"

class Client
{
    private:
        std::string _username;
        std::string _nickname;
        std::string _realname;
        std::string _serverName;
        std::string _hostname;
        std::string _clientIpAddr;
        int         _clientFd;

        std::set<Channel*>  _joinedChannels;

        bool    _hasEnteredPass;
        bool    _hasGivenNick;
        bool    _hasGivenUser;
        bool    _isAlreadyRegistered;

        std::string _cliBuff;

    public:
        Client( void );
        Client( Client const & other );
        Client& operator=( Client const & other );
        ~Client( void );

        //Getter:
        std::string getUsername( void ) const;
        std::string getNickname( void ) const;
        std::string getRealName() const;
        std::string getHostname() const;
        std::string getServerName() const;
        std::string getclientIP( void ) const;
        int getClientFd( void ) const;
        const std::set<Channel*>&  getJoinedChannels() const;
        bool    hasSentNick() const;
        bool    hasSentPass() const;
        bool    hasSentUser() const;
        bool    isRegistered() const;
        bool    isAlreadyRegistered() const;
        std::string getCliBuff() const;

        //Setter
        void    setUsername( const std::string& username );
        void    setNickname( const std::string& nickname );
        void    setRealName( const std::string& realname );
        void    setHostname( const std::string& hostname );
        void    setServerName( const std::string& servername );
        void    setClientIP( const std::string& clientIP );
        void    setClientFd( const int& fd );
        void    setSentPass(bool status);
        void    setSentNick(bool status);
        void    setSentUser(bool status);
        void    setIsAlreadyRegistered(bool status);
        void    setCliBuff(std::string buff);

        void    addChannel(Channel* channel);
        void    removeChannel(Channel* channel);
};

#endif