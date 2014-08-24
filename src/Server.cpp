//============================================================================
// Name        : Server.cpp from Testing
// Author      : Thog
// Version     : 1.0
// Copyright   : Copyright Thog 2014 - All right reserved
// Description : Basic implementation of an HTTP Server (WIP)
//============================================================================

#include "Server.h"

Server::Server(int *p) {
	sock_err = 0;
	port = p;
	recsize = sizeof(csin);
}

bool Server::init() {
	int *startupError = new int;
#if defined (WIN32)
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
				sock_err = listen(sock, 5);
				if (sock_err != SOCKET_ERROR) {
					this->manageConnexion();
				} else {
					cout << "Socket error when starting listening " << endl;
				}
			}

			/* Close Socket */
			closesocket(sock);
		}

#if defined (WIN32)
		WSACleanup();
#endif
	}
	return true;
}

string getHost(const char request[]) {
	string request_str(request);
	string::size_type start = request_str.find("Host: ");
	string::size_type finish = request_str.find('\n', start);
	string host = request_str.substr(start, finish);
	cout << start << " to " << finish << endl;
	return host;
}

void getFileContent(string filename, string &result) {
	result = "Not Found";
	ifstream file(filename, ios::in | ios::binary | ios::ate);
	if (file.is_open()) {
		int size;
		size = file.tellg();
		char content[size];

		file.seekg(0, ios::beg);
		file.read(content, size);
		cout << content << endl;
		file.close();
		result = string(content);
	}
}

void Server::manageConnexion() {
	while (1) {
		cout << "Waiting Client" << endl;
		client = accept(sock, (SOCKADDR*) &csin, &recsize);
		cout << "New Client" << endl;
		char request[512];
		//cout << request << endl;
		recv(client, request, sizeof(request), 0);
		//cout << getHost(request) << endl;
		delete request;
		char header[] = "HTTP/1.1 200 OK\r\n";
		char contentType[] = "Content-Type: text/plain\r\n";
		char emptyLine[] = "\r\n";

		string content = "";
		getFileContent("C:\\www\\index.html", content);

		//open string stream to convert int to string
		ostringstream oss;
		oss << content.size();
		string size = oss.str();
		std::string *contentLenght = new string("Content-Length: ");
		*contentLenght += size;
		*contentLenght += "\r\n";
		//cout << *contentLenght << endl;
		const int packetSize = sizeof(header) + sizeof(contentType)
				+ sizeof(emptyLine) + content.size() + (*contentLenght).size();

		//cout << packetSize << endl;
		char *buffer = new char[packetSize];

		//empty first char of the array
		*(buffer + 0) = '\0';

		strcat(buffer, header);

		strcat(buffer, contentType);

		strcat(buffer, (*contentLenght).c_str());

		delete contentLenght;
		strcat(buffer, emptyLine);
		strcat(buffer, content.c_str());

		sock_err = send(client, buffer, sizeof(char[packetSize]), 0);
		delete buffer;
		//cout << "CRASH AVANT ICI SVP";
		if (sock_err == SOCKET_ERROR)
			cout << "Transmition error" << endl;

		//Actually no support of keep-alive ( 3x more request :/ )
		shutdown(client, 2);
	}

}

