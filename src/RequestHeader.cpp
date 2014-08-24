//============================================================================
// Name        : RequestHeader.cpp from Testing
// Author      : Thog
// Version     : 1.0
// Copyright   : Copyright Thog 2014 - All right reserved
// Description : Nothing
//============================================================================

#include "RequestHeader.hpp"

RequestHeader::RequestHeader(string b) {

	header = new string;
	host = new string;
	agent = new string;
	destination = new string;
	buffer = new string;
	*buffer = b;
	string delimiter = "\r\n";
	string protocolVer("HTTP/1.1");
	size_t pos = (*buffer).find(protocolVer);
	if (pos != string::npos) {
		*header = (*buffer).substr(0, pos);
		if ((*header).find("GET") != string::npos) {
			*destination = (*header).substr(4, (*header).size());
		}

		else if ((*header).find("POST") != string::npos)
			*destination = (*header).substr(5, (*header).size());

		//acout << *destination << endl;
		//cout << *header <<endl;
		(*buffer).erase(0, pos + protocolVer.length());
	}
	string token;
	while ((pos = (*buffer).find(delimiter)) != string::npos) {
		token = (*buffer).substr(0, pos);
		//cout << token << endl;

		if (token.find("Host") != string::npos)
			*host = token.substr(6, pos);

		else if (token.find("User-Agent") != string::npos)
			*agent = token.substr(12, pos);

		(*buffer).erase(0, pos + delimiter.length());
	}

}

RequestHeader::~RequestHeader() {

	//cout << "Removing RequestHeader from memory" << endl;
	delete header;
	delete host;
	delete agent;
	delete destination;
	delete buffer;
}

string RequestHeader::getHead() {
	return *header;
}

string RequestHeader::getDestination() {
	return *destination;
}

string RequestHeader::getHost() {
	return *host;
}

string RequestHeader::getAgent() {
	return *agent;
}
