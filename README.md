LOG:

*29/05 16:20 by gwen*:
-Makefile okay
-Did all the init for class variables
-Port parsing work

*01/06 16:20 by gwen*:
-Added Command class for parsing (work)
-Added pointer function in server for command
-Added IRC server code
-Working on pre command handling

*02/06 14:00 by gwen*:
-Need to connect everything together (client information sending to command parsing and then command handling)
-Need to add signals


*03/06 14:00 by storck*:
-IRC server can succesfully be started, accept client and handel client input.
-Launch the program, then in another terminal, type :> nc localhost [port #]. Then have fun sending messages to server.

TODO:   Cleanly destroy a client when it disconnects.
        Manage client input as commands, right now it is only a string displayed by the server.

*03/06 14:10 by gwen*:
-Coded password and nickname handlers, have to test

## (for storck)
-If you can, create the function to send message to client asap so I will be able to test and correct it early

*04/06 17:00 by gwen*:
-Connection works, need to properly destroy everything the client has when he disconnects, otherwise the server will remember it and some commands may no work such as USER
-Command USER, NICK and PASS works (need to add disconnect function in PASS if it's pass wrong)
-Added welcome code

*05/06 12:30 by gwen*:

# Maneuver to get these problems with "valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all"
### Execute the server and then CTRL+C
Conditional jump or move depends on uninitialised value(s)
   at 0x40627E: Server::run() (Server.cpp:262)
   by 0x4121A0: main (main.cpp:38)

### Execute the server, execute the client, write a command via client and then CTRL+C with server
at operator new(unsigned long) (vg_replace_malloc.c:501)
    by Server::newClient() (Server.cpp:157)
    by Server::run() (Server.cpp:265)
    by main (main.cpp:38)