/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 12:41:19 by storck            #+#    #+#             */
/*   Updated: 2026/06/03 12:27:26 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "Include.hpp"

class Server
{
    private:

        typedef void (Server::*CmdHandler)(Client* client, const std::vector<std::string>& params);

        int                     _port;
        int                     _socket;
        static bool             _signal;
        struct pollfd           _fds[200];
        unsigned int            _clientNb;
        std::map<int, Client*>  _clients; // Using map for optimization with an int (FD) and pointer to Client
        std::string             _servPassword;
        char                    _buffer[1024];
        std::map<std::string, CmdHandler> _cmds;

        void    _handleNick(Client* client, const std::vector<std::string>& params);
        void    _handlePass(Client* client, const std::vector<std::string>& params);
        void    _handleUser(Client* client, const std::vector<std::string>& params);
        //void    _handleOper(Client* client, const std::vector<std::string>& params);
        //void    _handleMode(Client* client, const std::vector<std::string>& params);
        //void    _handleQuit(Client* client, const std::vector<std::string>& params);
        void    _handleJoin(Client* client, const std::vector<std::string>& params);
        //void    _handlePart(Client* client, const std::vector<std::string>& params);
        //void    _handleTopic(Client* client, const std::vector<std::string>& params);
        //void    _handleKick(Client* client, const std::vector<std::string>& params);
        void    _handlePrivMsg(Client* client, const std::vector<std::string>& params);
        //void    _handleNotice(Client* client, const std::vector<std::string>& params);

    public:
        Server( const int& port, const std::string& password);
        Server( Server const & other );
        Server& operator=( Server const & other );
        ~Server( void );

        void    treatCommand(Client* client, std::string raw_line);

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

        static void    signalHandler( int sig );
        void    clearBuff( void );
        void    newClient( void );
        void    clientInput( int fd );
        
};

#endif