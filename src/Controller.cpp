//============================================================================
// Name        : Controller.cpp from Testing
// Author      : Thog
// Version     : 1.0
// Copyright   : Copyright Thog 2014 - All right reserved
// Description : Nothing
//============================================================================

#include "Controller.hpp"

Controller::Controller(int *p) {

	port = p;
	server = new Server(this);
}

Controller::~Controller() {
	delete server;
}

bool Controller::init()
{
	return server->init();
}

int Controller::getPort() const
{
	return (*port);
}

