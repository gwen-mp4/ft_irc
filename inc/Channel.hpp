/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 12:41:05 by storck            #+#    #+#             */
/*   Updated: 2026/05/29 12:41:07 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "Include.hpp"

class Channel
{
    private:
        bool                _inviteOnly;
        bool                _topicRestr;
        bool                _userLimited;
        int                 _limit;
        std::string         _password;
        std::string         _topic;
        std::vector<Client> _operators;

    public:
        Channel( void );
        Channel( Channel const & other );
        Channel& operator=( Channel const & other );
        ~Channel( void );

        //Getter:
        bool        getInviteMode( void ) const;
        bool        getTopicRestr( void ) const;
        bool        getUserLimited( void ) const;
        int         getLimit( void ) const;
        std::string getPassword( void ) const;
        std::string getTpoic( void ) const;

        //Setter
        void    setInviteMode( bool mod );
        void    setTopicRestr( bool res );
        void    setUserLimited( bool lim );
        void    setLimit( int lim );
        void    setPassword( std::string newPassW );
        void    setTpoic( std::string newTopic );

};

#endif