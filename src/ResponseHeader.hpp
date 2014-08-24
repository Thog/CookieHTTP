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
using namespace std;
class ResponseHeader {
public:
	ResponseHeader(string destination, string host);
	virtual ~ResponseHeader();
	int getSize();
	char *getResponse();
	string getHeader(), getContentType(), getContent(), getContentLenght();

private:
	char *response;
	string *header, *contentType, *content, *contentLenght;
	int *size;
#if defined (_WIN32)
    const char *server_root =  "C:\\www\\";
#elif defined (linux)
    const char *server_root =  "/usr/local/apache/www/";
#endif
};

#endif /* RESPONSEHEADER_H_ */
