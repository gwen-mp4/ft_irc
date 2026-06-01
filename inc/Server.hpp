/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 12:41:19 by storck            #+#    #+#             */
/*   Updated: 2026/06/01 16:09:11 by gwen             ###   ########.fr       */
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
        std::map<int, Client*>    _clients; // Using map for optimization with an int (FD) and pointer to Client
        std::string             _servPassword;
        std::map<std::string, Command*> _cmds;

        void    _handleNick();
        void    _handlePass();
        void    _handleUser();
        void    _handleOper();
        void    _handleMode();
        void    _handleQuit();
        void    _handleJoin();
        void    _handlePart();
        void    _handleTopic();
        void    _handleKick();
        void    _handlePrivMsg();
        void    _handleNotice();

    public:
        Server( const int& port, const std::string& password);
        Server( Server const & other );
        Server& operator=( Server const & other );
        ~Server( void );

        void    treatCommand(Client* client, const Command& msg);

        void    sendClientMessage(int clientFD, std::string message);
        // For now, we don't need it or won't need it for later
        // //Getter:
        // int         getport( void ) const;
        // int         getSocket( void ) const;
        // bool        getSignal( void ) const;
        // Client*     getClient( int index ) const;
        // std::string getServPassword( void ) const;

        // //Setter
        // void    setport( int por );
        // void    setSocket( int soc );
        // void    setSignal( bool sig );
        // void    setServPassword( std::string );

        void    run( void );
        
};

#endif