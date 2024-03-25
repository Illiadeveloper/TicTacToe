#include <iostream>
#include"_Server.h"
#include"_Client.h"

int main(int argc, char *argv[])
{
    WSADATA wsaData;
    int WSAresu;
    if ((WSAresu = WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)) {
        std::cout << "[ERROR] WSAStartup failed == " << WSAresu << std::endl;
    }
    std::cout << "[LOG] WSAStartup stated" << std::endl;

    if (strcmp(argv[1], "0") == 0) {
        _Server::Bind();
        _Server::Accept();
        _Server::Close();
    }
    else if (strcmp(argv[1], "1") == 0) {
        _Client::Connect();
        _Client::Close();
    }
    else {
        std::cout << "[ERROR] Invalid argument." << std::endl;
        return 1;
    }

    std::cout << "[LOG] WSAStartup exited" << std::endl;
    WSACleanup();
}