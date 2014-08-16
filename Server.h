#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED
#define WIN32
#if defined (WIN32)
    #include <winsock2.h>
    typedef int socklen_t;
#elif defined (linux)
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #define INVALID_SOCKET -1
    #define SOCKET_ERROR -1
    #define closesocket(s) close(s)
    typedef int SOCKET;
    typedef struct sockaddr_in SOCKADDR_IN;
    typedef struct sockaddr SOCKADDR;
#endif

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;
class Server {
public:
    Server(const int &port = 8080);
    bool init();
    int getPort();

private:
    void manageConnexion();
    int sendData(const SOCKET client, const char buffer[]);

};


#endif // SERVER_H_INCLUDED
