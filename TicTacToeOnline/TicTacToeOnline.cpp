#include"_Server.h"
#include"_Client.h"
#include"TicTacToe.h"

#include<string>

int main(int argc, char* argv[])
{
    if (argc != 2 && argc != 3) {
        std::cout << "Usage:  TicTacToeOnline.exe" << " [mode] [address]" << std::endl << std::endl;
        std::cout << "Options:" << std::endl << "        mode       0 for Server, 1 for Client" << std::endl;
        std::cout << "        address    IP address to connect (required for Client mode)" << std::endl;
        return 1;
    }

    int mode = std::stoi(argv[1]);

    if (mode != 0 && mode != 1) {
        std::cout << "Invalid mode. Use 0 for Server, 1 for Client." << std::endl;
        return 1;
    }

    if (mode == 1 && argc != 3) {
        std::cout << "For Client mode, provide the server IP address as the third argument." << std::endl;
        return 1;
    }

    WSADATA wsaData;
    int WSAresu;
    if ((WSAresu = WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)) {
        std::cout << "[ERROR] WSAStartup failed == " << WSAresu << std::endl;
    }
    std::cout << "[LOG] WSAStartup stated" << std::endl;

    bool curPlayer = true; // 0 = X; 1 = O
    int pos;
    int result;
    bool moveMade = true;
    int WhoWin = 0; // 1 = X; 2 = O

    if (mode == 0) {
        _Server::Bind();
        _Server::Accept();
        _Server::Send((int)(!curPlayer));
        WhoWin = curPlayer ? 1 : 2;
        std::cout << "[LOG] curPlayer: " << curPlayer << std::endl;

        TicTacToe::InitializeBoard();
        TicTacToe::ShowBoard();
        while (true) {
            if (moveMade) {
                if (curPlayer) { std::cout << "Your turn "; }
                else { std::cout << "Enemy's turn... "; }
            }
            moveMade = false;

            if (curPlayer)
                std::cin >> pos;
            else {
                pos = _Server::Recv();
            }

            if ((result = TicTacToe::Turn(pos, !curPlayer)) == -1) {
                std::cout << "0 < pos < 10 ";
                continue;
            }
            else if (result == -2) {
                std::cout << "This position already taken ";
                continue;
            }

            if (curPlayer)
                _Server::Send(pos);

            TicTacToe::ShowBoard();
            curPlayer = !curPlayer;
            moveMade = true;

            if (result == 3) {
                std::cout << "Draw!!!" << std::endl;
                break;
            }

            if (result == WhoWin) {
                std::cout << "You lose!!!" << std::endl;
                break;
            }
            else if (result != 0) {
                std::cout << "You win!!!" << std::endl;
                break;
            }

        }
        _Server::Close();
    }
    else {
        _Client::Connect(argv[3]);
        curPlayer = _Client::Recv();
        WhoWin = curPlayer ? 1 : 2;
        std::cout << "[LOG] curPlayer: " << curPlayer << std::endl;

        TicTacToe::InitializeBoard();
        TicTacToe::ShowBoard();
        while (true) {
            if (moveMade) {
                if (curPlayer) { std::cout << "Your turn "; }
                else { std::cout << "Enemy's turn... "; }
            }
            moveMade = false;

            if (curPlayer)
                std::cin >> pos;
            else {
                pos = _Client::Recv();
            }

            if ((result = TicTacToe::Turn(pos, curPlayer)) == -1) {
                std::cout << "0 < pos < 10 ";
                continue;
            }
            else if (result == -2) {
                std::cout << "This position already taken ";
                continue;
            }

            if (curPlayer)
                _Client::Send(pos);

            TicTacToe::ShowBoard();
            curPlayer = !curPlayer;
            moveMade = true;

            if (result == 3) {
                std::cout << "Draw!!!" << std::endl;
                break;
            }

            if (result == WhoWin) {
                std::cout << "You lose!!!" << std::endl;
                break;
            }
            else if (result != 0) {
                std::cout << "You win!!!" << std::endl;
                break;
            }
        }
        _Client::Close();
    }
    std::cout << "[LOG] WSAStartup exited" << std::endl;
    WSACleanup();
}