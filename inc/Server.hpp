/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 12:41:19 by storck            #+#    #+#             */
/*   Updated: 2026/06/03 10:53:44 by storck           ###   ########.fr       */
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
        struct pollfd           _fds[200];
        unsigned int            _clientNb;
        std::map<int, Client*>  _clients; // Using map for optimization with an int (FD) and pointer to Client
        std::string             _servPassword;
        char                    _buffer[1024];
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

        void    clearBuff( void );
        void    newClient( void );
        void    clientInput( int fd );
        
};

#endif