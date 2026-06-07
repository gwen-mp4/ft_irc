# **Problems**:
-If two servers with the same port connects, only one will work and the other will have leaks
-Client is still in server when QUIT is called, need to SIGINT or SIGQUIT to quit or multiple input to *Ncat: Broken pipe.*

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
-Added JOIN command, FINALLY IT WORKS!!! (no leaks and FDs leaks for now)

*07/06 15:00 by gwen*:
-Updated *_handleJoin()*, now it disconnects client if password is invalid
-Updated *Server::run()*, now it handles correctly signals (SIGINT/SIGQUIT) cleared everything correctly
-Updated *Server::clearClient()*, it clears everything (FD, client, channels, operator and member)
-Recoded *_handleQuit()* and *_handlePart*
-Now **QUIT** and **PART** works perfectly (normally) (and except that QUIT doesn't quit completly the prompt but it does disconnect)
-Fixed all segfaults, leaks and FDs leaks due to server SIGINT and/or client SIGINT