//============================================================================
// Name        : Controller.hpp from Testing
// Author      : Thog
// Version     : 1.0
// Copyright   : Copyright Thog 2014 - All right reserved
// Description : Nothing
//============================================================================

#ifndef CONTROLLER_HPP_
#define CONTROLLER_HPP_
#include <iostream>
#include <string>
#include "HttpServer.hpp"
using namespace std;
class Server;

class Controller {

private:
	Server *server;
	int *port;
public:
	Controller(int *port = new int(8080));
	virtual ~Controller();
	bool sendData(char *buffer, int &size) const;
	int getPort() const;
	bool init();
};

#endif /* CONTROLLER_HPP_ */
