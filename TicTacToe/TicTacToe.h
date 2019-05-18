#pragma once
#include "Board.h"
#include "Move.h"

class TicTacToe
{
private:
	Board board_;
	unsigned int r_;
	move move_;

public:

	bool isWin();

	move game();
	void playerMove();
	void firstPlayerMove();
	void secondPlayerMove();

	TicTacToe(unsigned int size, unsigned int row);
	~TicTacToe();
};

