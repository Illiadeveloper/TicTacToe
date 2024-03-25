#include "TicTacToe.h"

char TicTacToe::board[3][3];
bool TicTacToe::curPlayer;

void TicTacToe::ShowBoard() noexcept
{
	system("cls");
	int pos = 1;

	std::cout << "+ - + - + - +               + - + - + - +" << std::endl;
	for (int i = 0; i < 3; ++i) {
		std::cout << "|";
		for (int j = 0; j < 3; ++j) {
			std::cout << " " << board[i][j] << " |";
		}
		if(i == 1) {
			std::cout << " ------------> |";
		}
		else {
			std::cout << "               |";
		}
		for (int j = 0; j < 3; ++j) {
			std::cout << " " << pos << " |";
			pos++;
		}
		std::cout << std::endl << "+ - + - + - +               + - + - + - +" << std::endl;
	}
}

void TicTacToe::InitializeBoard() noexcept
{
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			board[i][j] = ' ';
		}
	}
}

int TicTacToe::Turn(int position) noexcept
{
	if (position < 1 || position > 9) { return -1; }
	if (board[(position - 1) / 3][(position - 1) % 3] == ' ') {
		board[(position - 1) / 3][(position - 1) % 3] = curPlayer ? 'X' : 'Y';
	}
	else { return -2; }
	curPlayer = !curPlayer;
	return 0;
}