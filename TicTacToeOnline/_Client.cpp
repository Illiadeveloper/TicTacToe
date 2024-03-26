#include "_Client.h"

addrinfo _Client::hints;
addrinfo* _Client::servinfo;
addrinfo* _Client::p;
sockaddr_storage _Client::their_addr;
int _Client::rv;
int _Client::sockfd;
int _Client::numbytes;
char _Client::s[INET6_ADDRSTRLEN];
char _Client::buff[MAXDATASIZE];

void _Client::Connect(char* addr)
{
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	if ((rv = getaddrinfo(addr, PORT, &hints, &servinfo) != 0)) {
		std::cout << "[ERROR] getaddrinfo: " << gai_strerror(rv) << std::endl;
		return;
	}
	std::cout << "[LOG] getaddrinfo" << std::endl;
	std::cout << "[LOG] trying to connect..." << std::endl;
	for (p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
			closesocket(sockfd);
			std::cout << "[WAR] client: socket" << std::endl;
			continue;
		}

		if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			closesocket(sockfd);
			std::cout << "[WAR] client: connect" << std::endl;
			continue;
		}
		break;
	}

	if (p == NULL) {
		std::cout << "[ERROR] server failed to connect" << std::endl;
		return;
	}
	freeaddrinfo(servinfo);

	inet_ntop(p->ai_family, get_in_addr((sockaddr*)&p->ai_addr), s, sizeof(s));
	std::cout << "[LOG] client: connect to " << s << std::endl;
}

int _Client::Send(int _data)
{
	char _buff[sizeof(int)];
	memcpy(_buff, &_data, sizeof(int));

	if (send(sockfd, _buff, sizeof(int), 0) == -1) {
		std::cout << "[ERROR] can't send" << std::endl;
		closesocket(sockfd);
		return -1;
	}

	return 0;
}

int _Client::Recv()
{
	int numbytes;
	int position;

	char _buff[sizeof(int)];
	if ((numbytes = recv(sockfd, _buff, sizeof(int), 0)) == -1) {
		std::cout << "[ERROR] can't recv" << std::endl;
		closesocket(sockfd);
		return -1;
	}
	else if (numbytes == 0) {
		std::cout << "[LOG] Connection closed" << std::endl;
		closesocket(sockfd);
		return -2;
	}

	memcpy(&position, _buff, sizeof(int));
	return position;
}

void _Client::Close()
{
	closesocket(sockfd);
	std::cout << "[LOG] client close..." << std::endl;
}