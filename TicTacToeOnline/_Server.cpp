#include "_Server.h"

WSADATA _Server::wsaData;
addrinfo _Server::hints;
addrinfo* _Server::servinfo;
addrinfo* _Server::p;
int _Server::rv;
int _Server::sockfd;
char _Server::s[INET6_ADDRSTRLEN];

void _Server::Start()
{
    if ((rv = WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)) {
        std::cout << "[ERROR] WSAStartup failed == " << rv << std::endl;
        return;
    }
    std::cout << "[LOG] WSAStartup stated" << std::endl;
}


void _Server::Bind()
{
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    if ((rv = getaddrinfo("localhost", PORT, &hints, &servinfo)) != 0) {
        std::cout << "[ERROR] getaddrinfo: " << gai_strerror(rv) << std::endl;
        return;
    }

    std::cout << "[LOG] getaddrinfo" << std::endl;
    std::cout << "[LOG] trying to connect..." << std::endl;
    for (p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            closesocket(sockfd);
            std::cout << "[WAR]server: socket" << std::endl;
            continue;
        }
        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            closesocket(sockfd);
            std::cout << "[WAR] server: bind" << std::endl;
            continue;
        }
        break;
    }

    if (p == NULL) {
        std::cout << "[ERROR] server failed to bind" << std::endl;
        return;
    }
    freeaddrinfo(servinfo);
    
    if ((listen(sockfd, BACKLOG) == -1)) {
        std::cout << "[ERROR] listen" << std::endl;
        closesocket(sockfd);
    }

    std::cout << "Waiting for connection..." << std::endl;
}

void _Server::Close()
{
    WSACleanup();
    closesocket(sockfd);
    std::cout << "[LOG] Server close..." << std::endl;
}
