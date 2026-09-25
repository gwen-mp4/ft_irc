*This project has been created as part of the 42 curriculum by gwen, storck.*

## Description:

The objective of this project is to develop an IRC server using the C++ 98 standard.

The server must be capable of handling multiple clients simultaneously without hanging.

Forking is prohibited. All I/O operations must be non-blocking.

Only 1 poll() (or equivalent) can be used for handling all these operations (read, write, but also listen, and so forth).

Only the following features must be implemented:
- It must be able to authenticate, set a nickname, a username, join a channel, send and receive private messages using your reference client.
- All the messages sent from one client to a channel have to be forwarded to every other client that joined the channel.
- It must have operators and regular users.
- Then, it has to implement the commands that are specific to channel operators:
  - KICK: Eject a client from the channel
  - INVITE: Invite a client to the channel
  - TOPIC: Change or view the channel topic
  - MODE: Change the channel mode:
    - i: set/remove Invite-only channel
    - t: set/remove the restrictions of the TOPIC command to channel operators
    - k: set/remove the channel key (password)
    - o: give/take channel operator privilege
    - l: set/remove the user limit to channel

## Instructions:

Compile with:

    make

Delete .o files with:

    make clean

Delete .o files and executable with:

    make fclean

Recompile with:

    make re

Launch the server with:

    ./irserv [port] [password]

Connect to the server with:

    nc localhost [port]

Or with the IRC client irssi by doing:

    irssi
    /connect localhost [port]

## Ressources:

This page was used to understand how to set up the server with the proper protocol and use poll() to accept and recieve client input:

https://www.ibm.com/docs/fr/i/7.5.0?topic=designs-using-poll-instead-select

This git repository was used to understand the behaviour of IRC commands:

https://gist.github.com/im-portthis/995254f6405c0b2c297eb38201cdb9ca

As well as the following page:

https://www.mirc.com/help/html/index.html?basic_irc_commands.html

LLMs where used to help with debug.
