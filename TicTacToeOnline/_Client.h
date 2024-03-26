#pragma once
#include "_Header.h"
class _Client 
{
private:
	static addrinfo hints, *servinfo, *p;
	static sockaddr_storage their_addr;
	static int rv, sockfd, numbytes;
	static char s[INET6_ADDRSTRLEN];
	static char buff[MAXDATASIZE];
public:
	_Client() = delete;

	static void Connect(char* addr);
	static int Send(int _data);
	static int Recv();
	static void Close();
};

