#pragma once

#include "Exeptions.h"
#include "Board.h"
#include "Player.h"

class Computer
{
private:
	Board currentBoard_;
	unsigned int r_;
	player computer_;
	player human_;

public:
	Computer(Board& currentBoard,unsigned int r, player computer,player human);
	~Computer();

	int h(Board board);
	int minmax(Board board,player currentPLayer,unsigned int depthLevel);

	unsigned int* optimalMove();
};

