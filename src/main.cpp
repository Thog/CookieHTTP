//============================================================================
// Name        : main.cpp from Testing
// Author      : Thog
// Version     : 1.0
// Copyright   : Copyright Thog 2014 - All right reserved
// Description : Main ? What else ?
//============================================================================

#include "Server.h"
int main()
{
    int port(8080);
    Server s(&port);
    s.init();
	return 0;
}


