/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 12:41:12 by storck            #+#    #+#             */
/*   Updated: 2026/05/29 14:52:14 by storck           ###   ########.fr       */
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
        std::string _clientIPadd;
        int         _clientFd;

    public:
        Client( void );
        Client( std::string name );
        Client( Client const & other );
        Client& operator=( Client const & other );
        ~Client( void );

        //Getter:
        std::string getUsername( void ) const;
        std::string getNickname( void ) const;
        std::string getclientIP( void ) const;
        int         getClientFd( void ) const;

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