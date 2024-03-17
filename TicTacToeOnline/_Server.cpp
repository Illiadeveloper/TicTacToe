#include "_Server.h"


void _Server::Start()
{
    if ((rv = WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)) {
        std::cout << "[ERROR] WSAStartup failed == " << rv << std::endl;
        return;
    }
    std::cout << "[LOG] WSAStartup stated" << std::endl;
}


void _Server::Connect(const char* serAdd)
{
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    if ((rv = getaddrinfo(serAdd, PORT, &hints, &servinfo)) != 0) {
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
        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            closesocket(sockfd);
            std::cout << "[WAR] client: connect" << std::endl;
            continue;
        }
        break;
    }

    if (p == NULL) {
        std::cout << "[ERROR] client failed to connected" << std::endl;
        return;
    }
    freeaddrinfo(servinfo);
    inet_ntop(p->ai_family, get_in_addr(p->ai_addr), s, sizeof(s));
    std::cout << "[LOG] connected to " << s << std::endl;
}

void _Server::Close()
{
    WSACleanup();
    closesocket(sockfd);
}
