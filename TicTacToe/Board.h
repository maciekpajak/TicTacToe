#pragma once



class Board
{
private:
	unsigned int size_;
	char **board_;
public:

	Board();
	Board(unsigned int n);
	~Board();

	void display();

	bool isFull();

	void markO(int x, int y);
	void markX(int x, int y);

	unsigned int getSize() { return size_; }

	char operator()(int x, int y);
};

