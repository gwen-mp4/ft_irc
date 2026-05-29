#ifndef SERVER_HPP
#define SERVER_HPP

#include "Include.hpp"

class Server
{
    private:
        int                 _port;
        int                 _socket;
        bool                _signal;
        std::vector<Client> _clients;

    public:
        Server( void );
        Server( Server const & other );
        Server& operator=( Server const & other );
        ~Server( void );

        //Getter:
        int     getport( void ) const;
        int     getSocket( void ) const;
        bool    getSignal( void ) const;

        //Setter
        void    setport( int por );
        void    setSocket( int soc );
        void    setSignal( bool sig );
        
};

#endif