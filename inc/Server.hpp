/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 12:41:19 by storck            #+#    #+#             */
/*   Updated: 2026/05/29 15:12:11 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "Include.hpp"

class Server
{
    private:
        int                     _port;
        int                     _socket;
        bool                    _signal;
        unsigned int            _clientNb;
        std::vector<Client*>    _clients;
        std::string             _servPassword;

    public:
        Server( void );
        Server( Server const & other );
        Server& operator=( Server const & other );
        ~Server( void );

        //Getter:
        int         getport( void ) const;
        int         getSocket( void ) const;
        bool        getSignal( void ) const;
        Client*     getClient( int index ) const;
        std::string getServPassword( void ) const;

        //Setter
        void    setport( int por );
        void    setSocket( int soc );
        void    setSignal( bool sig );
        void    setServPassword( std::string );

        void    run( void );
        
};

#endif