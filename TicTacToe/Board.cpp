#include "Board.h"
#include <string>
#include <iostream>

#include "Exeptions.h"

Board::Board()
{
	size_ = 3;
	board_ = new char*[size_];
	for (int i = 0; i < size_; i++)
	{
		board_[i] = new char[size_];
		for (int j = 0; j < size_; j++)
			board_[i][j] = ' ';
	}
}

Board::Board(unsigned int n)
{
	if (n < 1)
		throw INVALID_SIZE_EXEPTION;
	size_ = n;
	board_ = new char*[n];
	for (int i = 0; i < n; i++)
	{
		board_[i] = new char[n];
		for (int j = 0; j < n; j++)
			board_[i][j] = ' ';
	}
}

Board::~Board()
{
}

void Board::display()
{
	for (int i = 0; i < size_; i++)
	{
		for (int j = 0; j < size_; j++)
		{
			std::cout << ' ' << board_[i][j] << ' ';
			if (j < size_ - 1)
				std::cout << '|';
		}
		std::cout << std::endl;
		if (i < size_ - 1)
		{
			for (int j = 0; j < size_; j++)
			{
				std::cout << "---";
				if (j < size_ - 1)
					std::cout << '+';
			}
		}
		std::cout << std::endl;
	}
}

bool Board::isFull()
{
	bool full = true;
	for (int i = 0; i < size_; i++)
		for (int j = 0; j < size_; j++)
			if (board_[i][j] == ' ')
				return false;
	return full;
}

void Board::markO(int x, int y)
{
	if (x < 0 or x > (size_ - 1) or y < 0 or y > (size_ - 1))
		throw INVALID_INDEX_EXEPTION;

	if (isFull())
		throw FULL_BOARD_EXEPTION;

	if (board_[y][x] != ' ')
		throw FIELD_OCCUPIED_EXEPTION;
	else
		board_[y][x] = 'O';
}

void Board::markX(int x, int y)
{
	if (x < 0 or x>(size_ - 1) or y < 0 or y>(size_ - 1))
		throw INVALID_INDEX_EXEPTION;

	if (isFull())
		throw FULL_BOARD_EXEPTION;

	if (board_[y][x] != ' ')
		throw FIELD_OCCUPIED_EXEPTION;

	else
		board_[y][x] = 'X';
}


char Board::operator()(int x, int y)
{
	if (x < 0 or x>(size_ - 1) or y < 0 or y>(size_ - 1))
		throw INVALID_INDEX_EXEPTION;
	else
		return board_[y][x];
}
