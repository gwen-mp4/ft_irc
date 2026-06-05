/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 12:41:19 by storck            #+#    #+#             */
/*   Updated: 2026/06/04 11:46:32 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

# ifndef BUFF_SIZE
#  define BUFF_SIZE 1024
# endif

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
        std::map<int, Client*>    _clients; // Using map for optimization with an int (FD) and pointer to Client
        std::map<std::string, Client*>  _clientsNick; // Searching clients by nickname
        std::string             _servPassword;
        char                    _buffer[BUFF_SIZE];
        std::map<std::string, CmdHandler> _cmds;
        std::map<std::string, Channel*> _channels;
        float                   _version;
        char*                   _creationTime;

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

        bool    validNickname(const std::string& nickname) const;
        bool    validUsername(const std::string& username) const;
        void    treatCommand(Client* client, std::string raw_line);

        void    sendClientMessage(int clientFD, std::string message) const;
        void    sendWelcomeMessage(Client* client) const;

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
        void    clearClient( int fd );
        void    newClient( void );
        void    clientInput( int fd );

        char*    getCreationDate( void ) const;
        
        template <typename T>
        std::string ft_itoa(T num) const;
};

# include "Utils.tpp"

#endif