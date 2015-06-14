//============================================================================
// Name        : main.cpp from Testing
// Author      : Thog
// Version     : 1.0
// Copyright   : Copyright Thog 2014 - All right reserved
// Description : Main ? What else ?
//============================================================================

#include "Controller.hpp"
int main()
{
    int port(80);
    Controller *c = new Controller(&port);
    c->init();
	return 0;
}


