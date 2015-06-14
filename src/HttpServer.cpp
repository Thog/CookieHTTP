//============================================================================
// Name        : HttpServer.cpp from Testing
// Author      : Thog
// Version     : 1.0
// Copyright   : Copyright Thog 2014 - All right reserved
// Description : Basic implementation of an HTTP Server (WIP)
//============================================================================

#include "RequestHeader.hpp"
#include "ResponseHeader.hpp"

Server::Server(Controller const *c) {
	controller = c;
	sock_err = 0;
	port = new int(c->getPort());
	recsize = sizeof(csin);
}

bool Server::init() {
	int *startupError = new int;
#if defined (_WIN32)
	WSADATA WSAData;
	*startupError = WSAStartup(MAKEWORD(2, 2), &WSAData);
#else
	*startupError = 0;
#endif

	if (!*startupError) {
		// Not reused so delete it
		delete startupError;

		sock = socket(AF_INET, SOCK_STREAM, 0);

		if (sock != INVALID_SOCKET) {
			cout << "Starting TCP/IP Server on port " << *port << endl;

			/* Configuration */
			sin.sin_addr.s_addr = htonl(INADDR_ANY); /* All IP */
			sin.sin_family = AF_INET; /* Protocol */
			sin.sin_port = htons(*port); /* Listen on port */
			cout << "Binding port " << *port << "..." << endl;
			sock_err = bind(sock, (SOCKADDR*) &sin, sizeof(sin));

			if (sock_err != SOCKET_ERROR) {
				cout << "Listening port " << *port << "..." << endl;
				delete port;
				sock_err = listen(sock, 500);
				if (sock_err != SOCKET_ERROR) {
					cout << "Server is running, waiting for client." << endl;
					this->manageConnexion();
				} else {
					cout << "Socket error when starting listening " << endl;
				}
			} else {
				cout << "Socket error when binding " << endl;
			}

			/* Close Socket */
			closesocket(sock);
		}

#if defined (_WIN32)
		WSACleanup();
#endif
	}
	return true;
}

void Server::manageConnexion() {

	while (1) {
		client = accept(sock, (SOCKADDR*) &csin, &recsize);
		char requestBuffer[512];

		//cout << request << endl;
		recv(client, requestBuffer, sizeof(requestBuffer), 0);
		RequestHeader *request = new RequestHeader(requestBuffer);
		cout << "[" << inet_ntoa(csin.sin_addr) << "] " << request->getHead() << endl;
		//cout << request.getAgent() << endl;
		//cout << request.getHost() << endl;

		ResponseHeader *response = new ResponseHeader(this, request->getDestination(), request->getHost());
		delete request;

		//sock_err = this->sendBufferData(response->getResponse(), response->getSize());
		delete response;

		//cout << "CRASH AVANT ICI SVP";
		if (sock_err == SOCKET_ERROR)
			cout << "Transmition error" << endl;

		//Actually no support keep-alive ( 3x more request :/ )
		this->close();
	}

}

