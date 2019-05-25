
#include "Computer.h"
#include <algorithm>
#include <iostream>
#include <vector>

Computer::Computer(Board& currentBoard, unsigned int r, player computer, player human)
{
	currentBoard_ = Board(currentBoard);
	r_ = r;
	computer_ = computer;
	human_ = human;
}

Computer::~Computer()
{
}

int Computer::minmax(Board board, player currentPlayer, unsigned int depthLevel)
{
	if (board.isFull()) return 0;
	if (currentPlayer == computer_ and board.isRinRow(r_)) return -1;
	if (currentPlayer == human_ and board.isRinRow(r_)) return 1;

	int min = 1, max = -1,tmp;
	for (unsigned int x = 0; x < board.getSize(); x++)
		for (unsigned int y = 0; y < board.getSize(); y++)
		{
			if (board.isFieldOccupied(x, y))
				continue;

			Board newBoard = Board(board);
			currentPlayer == player::X ? newBoard.markX(x, y) : newBoard.markO(x, y);

			if (currentPlayer == computer_)
			{
				tmp = minmax(newBoard, human_, depthLevel + 1);
				if (tmp > max) max = tmp; 
			}
			if (currentPlayer == human_)
			{
				tmp = minmax(newBoard, computer_, depthLevel + 1);
				if (tmp < min) min = tmp;
			}
		
		}
	if (currentPlayer == computer_) 
		return max;
	else if (currentPlayer == human_)
		return min;

}

unsigned int * Computer::optimalMove()
{
	unsigned int* optimalXY = new unsigned int[2];

	int maximum = -1;
	for (unsigned int x = 0; x < currentBoard_.getSize(); x++)
		for (unsigned int y = 0; y < currentBoard_.getSize(); y++)
		{
			Board newBoard = Board(currentBoard_);
			if (currentBoard_.isFieldOccupied(x, y))
				continue;
			computer_ == player::X ? newBoard.markX(x, y) : newBoard.markO(x, y);

			int tmp = minmax(newBoard, human_, 1);
			if (tmp > maximum)
			{
				optimalXY[0] = x;
				optimalXY[1] = y;
				maximum = tmp;
			}
		}

	optimalXY[0];
	optimalXY[1];
	return optimalXY;
}
