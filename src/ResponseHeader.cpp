//============================================================================
// Name        : ResponseHeader.cpp from Testing
// Author      : Thog
// Version     : 1.0
// Copyright   : Copyright Thog 2014 - All right reserved
// Description : Nothing
//============================================================================

#include "ResponseHeader.hpp"

inline void getFileContent(string path, string &result) {
	result = "Not Found ";
	ifstream file(path, ios::in | ios::binary | ios::ate);
	if (file.is_open()) {
		int size;
		size = file.tellg();
		char content[size];
		file.seekg(0, ios::beg);
		file.read(content, size);
		file.close();
		result = string(content);
	}

}

ResponseHeader::ResponseHeader(string destination, string  host) {

	header = new string;
	contentType = new string;
	content = new string;
	contentLenght = new string;
	size = new int;
	*content = "Access Denied";
	if (destination.find("../") == string::npos) {
		if (destination.find("/ ") != string::npos)
			destination = "/index.html";
		getFileContent(string(server_root) + host + "/" +  destination, *content);
		if ((*content) == "Not Found")
			getFileContent(string(server_root) + "default/" +  destination, *content);
	}

	*contentType = "Content-Type: text/html\r\n";
	ostringstream oss;
	oss << (*content).size();
	string size_str = oss.str();
	*contentLenght = "Content-Length: ";
	*contentLenght += size_str;
	*contentLenght += "\r\n";

	if ((*content) == "Not Found")
		*header = "HTTP/1.1 404 Not Found\r\n";
	else if ((*content) == "Access Denied")
		*header = "HTTP/1.1 403 Forbidden\r\n";
	else
		*header = "HTTP/1.1 200 OK\r\n";

	*size = (*header).size() + (*contentType).size() + sizeof("\r\n") + (*content).size() + (*contentLenght).size();

	response = new char[*size];

    //empty first char of the array
	*(response + 0) = '\0';

	strcat(response, (*header).c_str());
	strcat(response, (*contentType).c_str());
	strcat(response, (*contentLenght).c_str());
	strcat(response, "\r\n");
	strcat(response, (*content).c_str());
}

ResponseHeader::~ResponseHeader() {
	delete header;
	delete contentType;
	delete content;
	delete contentLenght;
	delete size;

}

int ResponseHeader::getSize()
{
	return *size;
}

char* ResponseHeader::getResponse()
{
	return response;
}

string ResponseHeader::getHeader()
{
	return *header;
}

string ResponseHeader::getContent()
{
	return *content;
}

string ResponseHeader::getContentLenght()
{
	return *contentLenght;
}

string ResponseHeader::getContentType()
{
	return *contentType;
}
