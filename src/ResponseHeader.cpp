//============================================================================
// Name        : ResponseHeader.cpp from Testing
// Author      : Thog
// Version     : 1.0
// Copyright   : Copyright Thog 2014 - All right reserved
// Description : Nothing
//============================================================================

#include "ResponseHeader.hpp"

inline void getFileContent(string path, string &result) {
	result = "Not Found";
	ifstream file(path, ios::in | ios::binary | ios::ate);
	if (file.is_open()) {
		vector<char> buffer;
		int size = file.tellg();
		buffer.resize(size);

		file.seekg(0, ios::beg);
		ostringstream oss;
		oss << file.rdbuf();
		file.close();
		result = oss.str();
	}

}

inline bool fileExist(string path)
{
	ifstream file(path, ios::in);
	return file.good();
}

ResponseHeader::ResponseHeader(const Server *s,string destination, string  host) {
	httpServer = s;
	header = new string;
	contentType = new string;
	content = new string;
	contentLenght = new string;
	server = new string;
	size = new int;
	*content = "Access Denied";
	if (destination.find("../") == string::npos) {
		if (destination.find("/ ") != string::npos)
			destination = "/index.html";
		//getFileContent(string(server_root) + host + "/" +  destination, *content);
		//if ((*content) == "Not Found")
		if(!fileExist(string(server_root) + host + "/" +  destination))
		{
			if(fileExist(string(server_root) + "default/" +  destination))
				getFileContent(string(server_root) + "default/" +  destination, *content);
			else
				*content = "Not Found";
		}
		else
		{
			getFileContent(string(server_root) + host + "/" +  destination, *content);
		}



			//getFileContent(string(server_root) + "default/" +  destination, *content);
	}
	unsigned int posExt = destination.rfind(".");
	//cout << (*content).c_str();
	*contentType = "Content-Type: text/html\r\n";
	if(posExt != string::npos)
	{
		string ext = destination.substr(posExt, destination.size());
		int max = ext.find(" ");
		//cout << max << endl;
		ext = ext.substr(0, max);

		//cout << ext << endl;
		*contentType = "Content-Type: " + getMineType(ext) + "\r\n";
	}





	ostringstream oss;
	oss << (*content).length() + 1;
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

	*server = "Server: CookieHTTP 0.1\r\n";
	*size = (*header).size() + (*server).size() +  (*contentType).size() + sizeof("\r\n") + (*contentLenght).size();

	response = new char[*size];

    //empty first char of the array
	*(response + 0) = '\0';

	strcat(response, (*header).c_str());
	strcat(response, (*server).c_str());
	strcat(response, (*contentType).c_str());
	strcat(response, (*contentLenght).c_str());
	strcat(response, "\r\n");
//	strcat(response, (*content).c_str());
	httpServer->sendBufferData(response, *size);
	httpServer->sendBufferData((*content).c_str(), (*content).length());
}

ResponseHeader::~ResponseHeader() {
	delete header;
	delete contentType;
	delete content;
	delete contentLenght;
	delete server;
	delete[] response;
	delete size;

}

int ResponseHeader::getSize()
{
	return *size;
}

char *ResponseHeader::getResponse()
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

inline string ResponseHeader::getMineType(string ext)
{
	string result = "text/html";
#if defined(_WIN32)
    // return mime type for extension
    HKEY hKey = NULL;


    //cout << "WIN32" << endl;
    // open registry key
    long t = RegOpenKeyEx(HKEY_CLASSES_ROOT, ext.c_str(),
                           0, KEY_READ, &hKey);
    //cout << t << endl;
    if (t == ERROR_SUCCESS)
    {
    	//cout << "REG" << endl;
        // define buffer
        char szBuffer[256] = {0};
        DWORD dwBuffSize = sizeof(szBuffer);

        // get content type
        if (RegQueryValueEx(hKey, "Content Type", NULL, NULL,
                       (LPBYTE)szBuffer, &dwBuffSize) == ERROR_SUCCESS)
        {
            // success
        	result = szBuffer;
        }

        // close key
        RegCloseKey(hKey);
    }

#elif defined (linux)
    //TODO: use magic
#endif


	return result;
}
