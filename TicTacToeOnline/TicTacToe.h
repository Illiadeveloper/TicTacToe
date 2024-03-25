#pragma once
#include"_Header.h"
class TicTacToe
{
private:
	static char board[3][3];
	static bool curPlayer;
public:
	TicTacToe() = delete;
	TicTacToe(const TicTacToe&) = delete;
	TicTacToe& operator=(const TicTacToe&&) = delete;

	static void ShowBoard() noexcept;
	static void InitializeBoard() noexcept;
	static int Turn(int position) noexcept;
};
