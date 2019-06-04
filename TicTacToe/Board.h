#pragma once
#include "Player.h"
#include <string>
#include <iostream>


#include "Exeptions.h"



class Board
{
private:
	unsigned int size_;
	char **board_;

	unsigned int indexOfLastAdded_X = -1;
	unsigned int indexOfLastAdded_Y = -1;

private:
	void markO(unsigned int x,unsigned int y);
	void markX(unsigned int x,unsigned int y);
	
	bool isRinRowHorizontal(unsigned int r, unsigned int y);
	bool isRinRowVertical(unsigned int r, unsigned int x);
	bool isRinRowDiagonally(unsigned int r);
	bool isRinRowDiagonal_RightDown(unsigned int r);
	bool isRinRowDiagonal_RightUp(unsigned int r);


	bool isPatterninRowHorizontal(std::string pattern, unsigned int y);
	bool isPatterninRowVertical(std::string pattern, unsigned int x);
	bool isPatterninRowDiagonal_RightDown(std::string pattern);
	bool isPatterninRowDiagonal_RightUp(std::string pattern);
	bool isPatterninRowDiagonally(std::string pattern);


public:
	
	Board();
	Board(unsigned int size);
	Board(const Board &copyBoard);
	~Board();

	void display();
	void clean();

	inline bool isFull();
	int howManyEmpty();

	void mark(player p, unsigned int x, unsigned int y);

	bool isFieldEmpty(unsigned int x, unsigned int y);
	bool isFieldOccupied(unsigned int x, unsigned int y);

	
	bool isRinRow(unsigned int r);
	bool isRinRowFast(unsigned int r);
	bool isPatternInRow(std::string pattern);

	unsigned int getSize() { return size_; }

	char operator()(unsigned int x,unsigned int y);
};

