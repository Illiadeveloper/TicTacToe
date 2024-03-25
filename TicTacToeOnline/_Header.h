#pragma once
#define PORT "9034"
#define WIN32_LEAN_AND_MEAN
#define BACKLOG 10
#define MAXDATASIZE 100

#include<iostream>
#include<Windows.h>
#include<WinSock2.h>
#include<WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")


inline void* get_in_addr(sockaddr* addr) {
	if (addr->sa_family == AF_INET) {
		return &(((sockaddr_in*)addr)->sin_addr);
	}
	return &(((sockaddr_in6*)addr)->sin6_addr);
}