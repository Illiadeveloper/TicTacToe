#pragma once
#include "_Header.h"
class _Server
{
private:
	static WSADATA wsaData;
	static addrinfo hints, *servinfo, *p;
	static int rv, sockfd;
	static char s[INET6_ADDRSTRLEN];

	_Server() {};
public:
	static void Start();
	static void Connect(const char* serAdd);
	static void Close();
};
