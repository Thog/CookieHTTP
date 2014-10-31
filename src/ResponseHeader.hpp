//============================================================================
// Name        : ResponseHeader.hpp from Testing
// Author      : Thog
// Version     : 1.0
// Copyright   : Copyright Thog 2014 - All right reserved
// Description : Nothing
//============================================================================

#ifndef RESPONSEHEADER_H_
#define RESPONSEHEADER_H_
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include "HttpServer.hpp"
#include <vector>


#if defined (_WIN32)
	#include <windows.h>
#elif defined (linux)

#endif
using namespace std;
class ResponseHeader {
public:
	ResponseHeader(const Server *s, string destination, string host);
	virtual ~ResponseHeader();
	ResponseHeader(const ResponseHeader &);
	int getSize();
	char *getResponse();
	inline string getMineType(string), getHeader(), getContentType(), getContent(), getContentLenght();

private:
	const Server *httpServer;
	char *response;
	string *header, *server, *contentType, *content, *contentLenght;
	int *size;
#if defined (_WIN32)
    const char *server_root =  "C:\\www\\";
#elif defined (linux)
    const char *server_root =  "/usr/local/apache/www/";
#endif
};

#endif /* RESPONSEHEADER_H_ */
