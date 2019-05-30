#include "Board.h"
#include <string>
#include <iostream>

#include "Exeptions.h"

Board::Board()
{
	size_ = 3;
	board_ = new char*[size_];
	for (unsigned int i = 0; i < size_; i++)
	{
		board_[i] = new char[size_];
		for (unsigned int j = 0; j < size_; j++)
			board_[i][j] = ' ';
	}
}

Board::Board(unsigned int size)
{
	if (size < 1)
		throw INVALID_SIZE_EXEPTION;
	size_ = size;
	board_ = new char*[size];
	for (unsigned int i = 0; i < size; i++)
	{
		board_[i] = new char[size];
		for (unsigned int j = 0; j < size; j++)
			board_[i][j] = ' ';
	}
}

Board::Board(const Board &copyBoard)
{
	size_ = copyBoard.size_;
	board_ = new char*[size_];
	for (unsigned int i = 0; i < size_; i++)
	{
		board_[i] = new char[size_];
		for (unsigned int j = 0; j < size_; j++)
			board_[i][j] = copyBoard.board_[i][j];
	}
}

Board::~Board()
{
	/*
	for (unsigned int i = 0; i < size_; i++)
	{
		delete board_[i];
	}
	delete board_;
	*/
}

void Board::display()
{
	for (unsigned int i = 0; i < size_; i++)
	{
		for (unsigned int j = 0; j < size_; j++)
		{
			std::cout << ' ' << board_[i][j] << ' ';
			if (j < size_ - 1)
				std::cout << '|';
		}
		std::cout << std::endl;
		if (i < size_ - 1)
		{
			for (unsigned int j = 0; j < size_; j++)
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
	for (unsigned int x = 0; x < size_; x++)
		for (unsigned int y = 0; y < size_; y++)
			if (isFieldEmpty(x,y))
				return false;
	return true;
}

void Board::mark(player p, unsigned int x, unsigned int y)
{
	p == player::X ? markX(x, y) : markO(x, y);
}

void Board::markO(unsigned int x, unsigned int y)
{
	if (x > (size_ - 1) or y > (size_ - 1))
		throw INVALID_INDEX_EXEPTION;

	if (isFull())
		throw FULL_BOARD_EXEPTION;

	if (isFieldOccupied(x, y))
		throw FIELD_OCCUPIED_EXEPTION;
	else
		board_[y][x] = 'O';
}

void Board::markX(unsigned int x, unsigned int y)
{
	if (x < 0 or x>(size_ - 1) or y < 0 or y>(size_ - 1))
		throw INVALID_INDEX_EXEPTION;

	if (isFull())
		throw FULL_BOARD_EXEPTION;

	if (isFieldOccupied(x,y))
		throw FIELD_OCCUPIED_EXEPTION;

	else
		board_[y][x] = 'X';
}

bool Board::isFieldEmpty(unsigned int x, unsigned int y)
{
	if (x > (size_ - 1) or y > (size_ - 1))
		throw INVALID_INDEX_EXEPTION;
	if (board_[y][x] == ' ')
		return true;
	else
		return false;
}

bool Board::isFieldOccupied(unsigned int x, unsigned int y)
{
	if (x > (size_ - 1) or y > (size_ - 1))
		throw INVALID_INDEX_EXEPTION;
	if (board_[y][x] != ' ')
		return true;
	else
		return false;
}

bool Board::isRinRowHorizontal(unsigned int r, unsigned int y)
{
	if (y < 0 or y >= size_)
		throw INVALID_INDEX_EXEPTION;
	std::string row(r, ' ');
	std::string rowX(r, 'X');
	std::string rowO(r, 'O');
	for (unsigned int i = 0; i < size_; i++)
	{
		row[i % r] = board_[y][i];
		if (row.compare(rowX) == 0 or row.compare(rowO) == 0) return true;
	}
	return false;
}

bool Board::isRinRowVertical(unsigned int r, unsigned int x)
{
	if (x < 0 or x>(size_ - 1))
		throw INVALID_INDEX_EXEPTION;
	std::string row(r, ' ');
	std::string rowX(r, 'X');
	std::string rowO(r, 'O');
	for (unsigned int i = 0; i < size_; i++)
	{
		row[i % r] = board_[i][x];
		if (row.compare(rowX) == 0 or row.compare(rowO) == 0) return true;
	}
	return false;
}

bool Board::isRinRowDiagonally(unsigned int r)
{
	unsigned int boardSize = size_;
	int tmp1 = 0;
	std::string row(r, ' ');
	std::string reset(r, ' ');
	std::string rowX(r, 'X');
	std::string rowO(r, 'O');
	int y, x, k;
	for (k = 0; k <= boardSize - r; k++)
	{
		for (x = 0, y = k; x < boardSize and y < boardSize; x++, y++, tmp1++)
		{
			row[tmp1 % r] = board_[y][x];
			if (row.compare(rowX) == 0 or row.compare(rowO) == 0) return true;
		}
		row = reset; tmp1 = 0;

		for (x = k, y = 0; x < boardSize and y < boardSize; x++, y++, tmp1++)
		{
			row[tmp1 % r] = board_[y][x];
			if (row.compare(rowX) == 0 or row.compare(rowO) == 0) return true;
		}
		row = reset; tmp1 = 0;

		for (x = k, y = boardSize - 1; x < boardSize and y >= 0; x++, y--, tmp1++)
		{
			row[tmp1 % r] = board_[y][x];
			if (row.compare(rowX) == 0 or row.compare(rowO) == 0) return true;
		}
		row = reset; tmp1 = 0;

		for (x = 0, y = boardSize - 1 - k; x < boardSize and y >= 0; x++, y--, tmp1++)
		{
			row[tmp1 % r] = board_[y][x];
			if (row.compare(rowX) == 0 or row.compare(rowO) == 0) return true;
		}
		row = reset; tmp1 = 0;

	}
	return false;
}

bool Board::isRinRow(unsigned int r)
{
	for (unsigned int i = 0; i < size_; i++)
	{
		if (isRinRowHorizontal(r, i)) return true;
		if (isRinRowVertical(r, i)) return true;
		if (isRinRowDiagonally(r)) return true;
	}
	return false;
}

char Board::operator()(unsigned int x,unsigned int y)
{
	if (x > (size_ - 1) or y > (size_ - 1))
		throw INVALID_INDEX_EXEPTION;
	else
		return board_[y][x];
}
