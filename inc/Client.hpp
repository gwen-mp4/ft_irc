/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 12:41:12 by storck            #+#    #+#             */
/*   Updated: 2026/06/01 15:42:26 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Include.hpp"

class Client
{
    protected:
        std::string _username;
        std::string _nickname;
        std::string _clientIpAddr;
        int         _clientFd;

        std::set<Channel*>  _joinedChannels;
        
        bool    _isOperator;

        bool    _hasEnteredPass;
        bool    _hasGivenNick;
        bool    _hasGivenUser;
        bool    _isRegistered; // Is true when all 3 above are true

    public:
        Client( const std::string& name, const std::string& nick );
        Client( Client const & other );
        Client& operator=( Client const & other );
        ~Client( void );

        //Getter:
        std::string getUsername( void ) const;
        std::string getNickname( void ) const;
        std::string getclientIP( void ) const;
        int getClientFd( void ) const;
        std::set<Channel*>  getJoinedChannels() const;
        bool    hasSentNick() const;
        bool    hasSentPass() const;
        bool    hasSentUser() const;
        bool    isRegistered() const;

        //Setter
        void    setUsername( const std::string& username );
        void    setNickname( const std::string& nickname );
        void    setclientIP( const std::string& clientIP );
        void    setClientFd( const int& fd );
        void    setSentPass(bool status);
        void    setSentNick(bool status);
        void    setSentUser(bool status);
};

class Operator: public Client
{
    private:

    public:
    
};

#endif