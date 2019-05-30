#pragma once
#include "Player.h"

class Board
{
private:
	unsigned int size_;
	char **board_;

private:
	void markO(unsigned int x,unsigned int y);
	void markX(unsigned int x,unsigned int y);
	
	bool isRinRowHorizontal(unsigned int r, unsigned int y);
	bool isRinRowVertical(unsigned int r, unsigned int x);
	bool isRinRowDiagonally(unsigned int r);
public:

	Board();
	Board(unsigned int size);
	Board(const Board &copyBoard);
	~Board();

	void display();

	inline bool isFull();

	void mark(player p, unsigned int x, unsigned int y);

	bool isFieldEmpty(unsigned int x, unsigned int y);
	bool isFieldOccupied(unsigned int x, unsigned int y);

	bool isRinRow(unsigned int r);

	unsigned int getSize() { return size_; }

	char operator()(unsigned int x,unsigned int y);
};

