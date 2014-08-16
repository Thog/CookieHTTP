#include "Server.h"

int port, sock_err;
SOCKET sock;
SOCKADDR_IN sin;
SOCKET csock;
SOCKADDR_IN csin;
socklen_t recsize;
Server::Server(const int& p)
{
    port = p;
}

bool Server::init()
{
    #if defined (WIN32)
        WSADATA WSAData;
        int erreur = WSAStartup(MAKEWORD(2,2), &WSAData);
    #else
        int erreur = 0;
    #endif



    recsize = sizeof(csin);

    if(!erreur)
    {
        sock = socket(AF_INET, SOCK_STREAM, 0);

        if(sock != INVALID_SOCKET)
        {
            cout << "Starting TCP/IP Server on port " << port << endl;

            /* Configuration */
            sin.sin_addr.s_addr    = htonl(INADDR_ANY);   /* Adresse IP automatique */
            sin.sin_family         = AF_INET;             /* Protocole familial (IP) */
            sin.sin_port           = htons(port);         /* Listage du port */
            sock_err = bind(sock, (SOCKADDR*)&sin, sizeof(sin));

            if(sock_err != SOCKET_ERROR)
            {
                sock_err = listen(sock, 5);
                if(sock_err != SOCKET_ERROR)
                {
                    this->manageConnexion();
                }
            }

            /* Close Socket */
            //closesocket(sock);
        }

        #if defined (WIN32)
            WSACleanup();
        #endif
    }
    return true;
}

int Server::getPort()
{
    return port;
}



void Server::manageConnexion()
{
//        char buffer[] = "HTTP/1.1 200 OK\r\n"
//              "Content-Type: text/plain\r\n"
//              "Content-Length: 3\r\n"        // Always set Content-Length
//              "\r\n"
//              "lol";
                   while(1)
                    {

                    /* Attente pendant laquelle le client se connecte */
                    cout << "Waiting Client" << endl;
                    csock = accept(sock, (SOCKADDR*)&csin, &recsize);
                    cout << "New Client" <<endl;
                    char request[32];
                    recv(csock, request, sizeof(request), 0);

                    char header[] = "HTTP/1.1 200 OK\r\n";
                    char contentType[] = "Content-Type: text/plain\r\n";
                    char emptyLine[] = "\r\n";
                    char content[] = "CHROME C'EST LA VIE";

                    //open string stream to convert int to string
                    ostringstream ss;
                    ss << char_traits<char>::length(content);

                    std::string contentLenght = "Content-Length: ";
                    contentLenght += ss.str();
                    contentLenght += "\r\n";
                    //const char *contentLenght = new char[contentl.size()];
                    //contentLenght = contentl.c_str();
                    const int packetSize = sizeof(header) + sizeof(contentType) + sizeof(emptyLine) + sizeof(content) + contentLenght.size();
                    cout << packetSize << endl;
                    char buffer[packetSize - 1];
                    //buffer[0] = 0;
                    //problems here
                    //cout << buffer[0] << endl;
                    strcat(buffer, header);
                    strcat(buffer, contentType);
                    strcat(buffer, contentLenght.c_str());
                    strcat(buffer, emptyLine);
                    strcat(buffer, content);
                    //strcat()
                    //cout << "Received data :" << request << endl;
                    cout << "Sending Data ..." << endl;
                    //cout << sizeof(buffer[4]) << endl;
                    sock_err = send(csock, buffer, sizeof(buffer), 0);

                    if(sock_err != SOCKET_ERROR)
                        cout << "Buffer : " << buffer << " sended" << endl;
                    else
                        cout << "Transmition error" << endl;

                    shutdown(csock, 2);
                }
}
