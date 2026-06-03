/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 12:41:12 by storck            #+#    #+#             */
/*   Updated: 2026/06/03 10:12:46 by storck           ###   ########.fr       */
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
        
        bool    _hasEnteredPass;
        bool    _hasGivenNick;
        bool    _hasGivenUser;
        bool    _isRegistered; // Is true when all 3 above are true

    public:
        Client( void );
        Client( const std::string& name, const std::string& nick );
        Client( Client const & other );
        Client& operator=( Client const & other );
        ~Client( void );

        // For now, we don't need it or won't need it for later
        // //Getter:
        // std::string getUsername( void ) const;
        // std::string getNickname( void ) const;
        // std::string getclientIP( void ) const;
        int getClientFd( void ) const;
        bool    isRegistered() const;

        //Setter
        void    setUsername( std::string username );
        void    setNickname( std::string nickname );
        void    setclientIP( std::string clientIP );
        void    setClientFd( int fd );

};

class Operator: public Client
{
    private:

    public:
    
};

#endif