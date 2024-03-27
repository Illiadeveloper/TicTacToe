#include "_Server.h"

addrinfo _Server::hints;
addrinfo* _Server::servinfo;
addrinfo* _Server::p;
sockaddr_storage _Server::their_addr;
int _Server::rv;
int _Server::sockfd;
int _Server::new_fd;
char _Server::s[INET6_ADDRSTRLEN];


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
    std::cout << "[LOG] trying to bind..." << std::endl;
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
    std::cout << "[LOG] Server connected" << std::endl;
    freeaddrinfo(servinfo);
    
    if ((listen(sockfd, BACKLOG) == -1)) {
        std::cout << "[ERROR] listen" << std::endl;
        closesocket(sockfd);
    }

    std::cout << "[LOG] Server has started listen" << std::endl;
}

void _Server::Accept()
{
    int size_addr = sizeof(their_addr);

    std::cout << "[LOG] Waiting for connection..." << std::endl;

    new_fd = accept(sockfd, (sockaddr*)&their_addr, &size_addr);
    if (new_fd == -1) {
        std::cout << "[WAR] accept" << std::endl;
        return;
    }
    inet_ntop(their_addr.ss_family, get_in_addr((sockaddr*)&their_addr), s, sizeof(s));
    std::cout << "[LOG] got connect from " << s << std::endl;
}

int _Server::Send(int position)
{
    char buff[sizeof(int)];
    memcpy(buff, &position, sizeof(position));

    if (send(new_fd, buff, sizeof(buff), 0) == -1) {
        std::cout << "[ERROR] can't send" << std::endl;
        closesocket(new_fd);
        return -1;
    }

    return 0;
}

int _Server::Recv()
{
    int numbytes;
    int position;

    char buff[sizeof(int)];
    if ((numbytes = recv(new_fd, buff, sizeof(buff), 0)) == -1) {
        std::cout << "[ERROR] can't recv" << std::endl;
        closesocket(new_fd);
        return -1;
    }
    else if (numbytes == 0) {
        std::cout << "[LOG] Connection closed" << std::endl;
        closesocket(new_fd);
        return -2;
    }

    memcpy(&position, buff, sizeof(buff));
    return position;
}

void _Server::Close()
{
    closesocket(sockfd);
    closesocket(new_fd);
    std::cout << "[LOG] Server close..." << std::endl;
}
