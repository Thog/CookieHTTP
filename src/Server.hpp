//============================================================================
// Name        : Server.hpp from Testing
// Author      : Thog
// Version     : 1.0
// Copyright   : Copyright Thog 2014 - All right reserved
// Description : Basic implementation of an HTTP Server (WIP)
//============================================================================

#ifndef SERVER_HPP_INCLUDED
#define SERVER_HPP_INCLUDED

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined (_WIN32)
    #include <windows.h>
    #include <winsock2.h>
    typedef int socklen_t;
#elif defined (linux)
    #define HTTP_ROOT "/usr/local/apache/www"
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <magic.h>
    #define INVALID_SOCKET -1
    #define SOCKET_ERROR -1
    #define closesocket(s) close(s)
    typedef int SOCKET;
    typedef struct sockaddr_in SOCKADDR_IN;
    typedef struct sockaddr SOCKADDR;
#endif



using namespace std;
class Server {
public:
    Server(int *);
    bool init();

private:
    void manageConnexion();
    /**
     The server socket
    **/
    SOCKET sock;

    /**
     The server socket configuration
    **/
    SOCKADDR_IN sin;

    /**
     The client socket
    **/
    SOCKET client;

    SOCKADDR_IN csin;

    socklen_t recsize;

    int *port, sock_err;
#if defined (_WIN32)
    const char *server_root =  "C:\\www\\";
#elif defined (linux)
    const char *server_root =  "/usr/local/apache/www";
#endif

};


#endif // SERVER_H_INCLUDED
