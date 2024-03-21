#pragma once
#include "_Header.h"
class _Server
{
private:
	static addrinfo hints, *servinfo, *p;
	static sockaddr_storage their_addr;
	static int rv, sockfd, new_fd;
	static char s[INET6_ADDRSTRLEN];
public:
	_Server() = delete;

	static void Bind();
	static void Accept();
	static void Close();
};
