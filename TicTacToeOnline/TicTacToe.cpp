#include "TicTacToe.h"

char TicTacToe::board[3][3];

int TicTacToe::CheckGameStatus() noexcept
{
	bool allFilled = true;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (board[i][j] == ' ') {
				allFilled = false;
				break;
			}
		}
		if (!allFilled) break;
	}

	if (allFilled)
		return 3;

	for (int i = 0; i < 3; ++i) {
		if (board[i][0] == 'X' && board[i][1] == 'X' && board[i][2] == 'X')
			return 1;
		if (board[0][i] == 'X' && board[1][i] == 'X' && board[2][i] == 'X')
			return 1;
	}
	if (board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'X')
		return 1;
	if (board[0][2] == 'X' && board[1][1] == 'X' && board[2][0] == 'X')
		return 1;


	for (int i = 0; i < 3; ++i) {
		if (board[i][0] == 'O' && board[i][1] == 'O' && board[i][2] == 'O')
			return 2;
		if (board[0][i] == 'O' && board[1][i] == 'O' && board[2][i] == 'O')
			return 2;
	}
	if (board[0][0] == 'O' && board[1][1] == 'O' && board[2][2] == 'O')
		return 2;
	if (board[0][2] == 'O' && board[1][1] == 'O' && board[2][0] == 'O')
		return 2;

	return 0;
}

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

int TicTacToe::Turn(int position, bool curPlayer) noexcept
{
	if (position < 1 || position > 9) { return -1; }
	if (board[(position - 1) / 3][(position - 1) % 3] == ' ') {
		board[(position - 1) / 3][(position - 1) % 3] = curPlayer ? 'X' : 'O';
	}
	else { return -2; }
	return CheckGameStatus();
}