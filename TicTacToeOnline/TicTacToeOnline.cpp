#include <iostream>
#include"_Server.h"

int main()
{
    WSADATA wsaData;
    int WSAresu;
    if ((WSAresu = WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)) {
        std::cout << "[ERROR] WSAStartup failed == " << WSAresu << std::endl;
    }
    std::cout << "[LOG] WSAStartup stated" << std::endl;

    _Server::Bind();
    _Server::Accept();
    _Server::Close();
}