//============================================================================
// Name        : RequestHeader.hpp from Testing
// Author      : Thog
// Version     : 1.0
// Copyright   : Copyright Thog 2014 - All right reserved
// Description : Nothing
//============================================================================

#ifndef REQUESTHEADER_H_
#define REQUESTHEADER_H_
#include <iostream>
#include <string>
#include <stdlib.h>
#if defined (_WIN32)

#endif
#if defined (linux)

#endif
using namespace std;

class RequestHeader {
public:
	RequestHeader(string);
	virtual ~RequestHeader();
	string getDestination(), getHost(), getHead(), getAgent();

private:
	string *header, *destination, *host, *agent, *buffer;
};

#endif /* REQUESTHEADER_H_ */
