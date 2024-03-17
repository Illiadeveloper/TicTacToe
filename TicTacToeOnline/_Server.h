#pragma once
#include "_Header.h"
class _Server
{
private:
	static WSADATA wsaData;
	static addrinfo hints, *servinfo, *p;
	static int rv, sockfd;
	static char s[INET6_ADDRSTRLEN];
public:
	_Server() = delete;

	static void Start();
	static void Bind();
	static void Close();
};
