#include "TicTacToe.h"


bool TicTacToe::isWin()
{
	//std::chrono::duration<double> T;
	//auto start = std::chrono::system_clock::now();
	bool pattern = board_->isRinRowFast(r_);
	//bool pattern = board_->isRinRow(r_);
	//auto end = std::chrono::system_clock::now();
	//T = end - start;
	//std::cout << T.count() << std::endl;
	return pattern == true ? true : false;
}

void TicTacToe::init(sf::RenderWindow &screen)
{
	randSymbols();
	randStartPlayer();
	std::cout << "Zaczyna symbol: " << (char)currentPlayer_ << std::endl;
	board_->display();

	sf::Texture tekstura;
	tekstura.loadFromFile("Graphics/field.png");
	sf::Sprite field_sprite;
	field_sprite.setTexture(tekstura);

	double scale_x = (double)SCREEN_X / size_ / FIELD_SIZE;
	double scale_y = (double)SCREEN_Y / size_ / FIELD_SIZE;

	field_sprite.scale(scale_x, scale_y);
	screen.clear(sf::Color::Black);
	for (int x = 0; x < size_; x++)
		for (int y = 0; y < size_; y++)
		{
			field_sprite.setPosition(x*SCREEN_X / size_, y*SCREEN_Y / size_);
			screen.draw(field_sprite);
		}
	screen.display();
}

void TicTacToe::play()
{
	
	sf::RenderWindow screen(sf::VideoMode(SCREEN_X, SCREEN_Y, 32), "TIC TAC TOE",sf::Style::Titlebar);
	sf::Vector2i pozycjaMyszyWzgledemOkna;

	init(screen);
	bool canMove = true;
	while (screen.isOpen())
	{
		sf::Event zdarzenie;
		while (screen.pollEvent(zdarzenie))
		{
			if (zdarzenie.type == sf::Event::Closed)
				screen.close();

			if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Escape)
				screen.close();

			if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::R)
			{
				reset();
				init(screen);
				canMove = true;
			}
			
			if (currentPlayer_ == computer_ and canMove)
			{
				graphicComputerMove(screen);
				board_->display();
				if (board_->isFull() and !isWin())
				{
					sf::Texture tekstura;
					tekstura.loadFromFile("Graphics/draw.png");
					sf::Sprite winner_sprite;
					winner_sprite.setTexture(tekstura);
					screen.draw(winner_sprite);
					canMove = false;
				}
				if (isWin())
				{
					winner_ = currentPlayer_;
					isDraw_ = false;
					sf::Texture tekstura;
					if (winner_ == player::O)
						tekstura.loadFromFile("Graphics/winnerO.png");
					else
						tekstura.loadFromFile("Graphics/winnerX.png");
					sf::Sprite winner_sprite;
					winner_sprite.setTexture(tekstura);
					screen.draw(winner_sprite);
					canMove = false;
				}

				changeTurn();
			}

			if (zdarzenie.type == sf::Event::MouseButtonPressed and zdarzenie.mouseButton.button == sf::Mouse::Left)
			{
				pozycjaMyszyWzgledemOkna = sf::Mouse::getPosition(screen);
				if(currentPlayer_ == player_ and canMove)
				if (graphicPlayerMove(pozycjaMyszyWzgledemOkna, screen))
				{
					//system("CLS");
					board_->display();
					if (board_->isFull() and !isWin())
					{
						sf::Texture tekstura;
						tekstura.loadFromFile("Graphics/draw.png");
						sf::Sprite winner_sprite;
						winner_sprite.setTexture(tekstura);
						screen.draw(winner_sprite);
						canMove = false;
					}
					if (isWin())
					{
						winner_ = currentPlayer_;
						isDraw_ = false;
						sf::Texture tekstura;
						if (winner_ == player::O)
							tekstura.loadFromFile("Graphics/winnerO.png");
						else
							tekstura.loadFromFile("Graphics/winnerX.png");
						sf::Sprite winner_sprite;
						winner_sprite.setTexture(tekstura);
						screen.draw(winner_sprite);
						canMove = false;
					}
					changeTurn();
				}
			}

			screen.display();
		}
	}
}

void TicTacToe::reset()
{
	board_->clean();
	isDraw_ = true;
	howManyEmpty_ = board_->getSize()*board_->getSize();
}


/*
void TicTacToe::play()
{
	init();
	while(!board.isFull())
	{
		std::cout << "Tura gracza: " << (char)currentPlayer_ << std::endl;
		move(currentPlayer_, screen);
		//system("CLS");
		board_->display();
		if (isWin())
		{
			winner_ = currentPlayer_;
			isDraw_ = false;
			break;
		}
		changeTurn();
	}

}
*/


void TicTacToe::randStartPlayer()
{
	srand((unsigned int)time(NULL));
	int i = rand() % 2;
	if (i == 1)
		currentPlayer_ = player::X;
	else
		currentPlayer_ = player::O;
}

void TicTacToe::randSymbols()
{
	srand((unsigned int)time(NULL));
	int i = rand() % 2 + 1;
	if (i == 1)
	{
		player_ = player::X;
		computer_ = player::O;
	}
	else
	{
		player_ = player::O;
		computer_ = player::X;
	}
}

void TicTacToe::changeTurn()
{
	currentPlayer_ == computer_ ? currentPlayer_ = player_ : currentPlayer_ = computer_;
}

void TicTacToe::move(player p)
{
	p == computer_ ? computerMove() : playerMove();
	//p == computer_ ? playerMove() : playerMove();  //test
}

int TicTacToe::minmax_computer(Board board, unsigned int depthLevel, int alpha, int beta)
{
	//std::cout << depthLevel << "->";
	if (board.isRinRowFast(r_)) { return PLAYER_WIN_VALUE; }
	if (board.isFull()) {  return DRAW; }
	if (depthLevel >= maxDepthLevel_) return h(board);
	
	for (unsigned int x = 0; x < board.getSize(); x++)
	{
		for (unsigned int y = 0; y < board.getSize(); y++)
		{
			if (board.isFieldOccupied(x, y))
				continue;

			Board newBoard = Board(board);
			newBoard.mark(computer_, x, y);

			alpha = std::max(alpha, minmax_player(newBoard, depthLevel + 1, alpha, beta));
			if (alpha == COMPUTER_WIN_VALUE) return alpha;
			if (alpha >= beta) return beta;
		}
	}

	return alpha;

}

int TicTacToe::minmax_player(Board board, unsigned int depthLevel, int alpha, int beta)
{
	//std::cout << depthLevel << "->";
	if (board.isRinRowFast(r_)) { return COMPUTER_WIN_VALUE; }
	if (board.isFull()){ return DRAW;}
	if (depthLevel >= maxDepthLevel_) return h(board);

	for (unsigned int x = 0; x < board.getSize(); x++)
	{
		for (unsigned int y = 0; y < board.getSize(); y++)
		{
			if (board.isFieldOccupied(x, y))
				continue;

			Board newBoard = Board(board);
			newBoard.mark(player_, x, y);

			beta = std::min(beta, minmax_computer(newBoard, depthLevel + 1, alpha, beta));
			if (beta == PLAYER_WIN_VALUE) return beta;
			if (alpha >= beta) return alpha;

		}
	}
	return beta;
}

void TicTacToe::computerMove()
{
	std::chrono::duration<double> T;
	auto start = std::chrono::system_clock::now();

	Board currentBoard(*board_);
	unsigned int optimalXY[2] = { 0,0 };
	int maximum = PLAYER_WIN_VALUE;
	for (unsigned int x = 0; x < currentBoard.getSize(); x++)
	{
		for (unsigned int y = 0; y < currentBoard.getSize(); y++)
		{
			
			if (currentBoard.isFieldOccupied(x, y))
				continue;
			Board newBoard(currentBoard);
			newBoard.mark(computer_, x, y);
			std::cout << "Mysle... ";		
			int pattern = minmax_player(newBoard, 1, PLAYER_WIN_VALUE, COMPUTER_WIN_VALUE);

			std::cout << pattern << std::endl;
			//if (pattern == PLAYER_WIN_VALUE)
			//	continue;
			if (pattern == COMPUTER_WIN_VALUE)
			{
				board_->mark(computer_, x, y);
				auto end = std::chrono::system_clock::now();
				T = end - start;
				std::cout << T.count() << std::endl;
				return;
			}
			if (pattern >= maximum)
			{
				optimalXY[0] = x;
				optimalXY[1] = y;
				maximum = pattern;
			}
			
			
			
		}
	}
	board_->mark(computer_,optimalXY[0], optimalXY[1]);


}

void TicTacToe::playerMove()
{


	unsigned int x, y;
	std::cout << "Podaj wspolrzedne (x,y): ";
	bool isExeption;
	do
	{
		std::cin >> x >> y;
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		isExeption = false;
		try
		{
			board_->mark(player_, x, y);
		}
		catch (int exeption)
		{
			switch (exeption)
			{
			case INVALID_INDEX_EXEPTION:
			{
				std::cout << "Nieprawidlowe wpolrzedne. Podaj jeszcze raz: ";
				break;
			}
			case FULL_BOARD_EXEPTION:
			{
				std::cout << "Plansza zapelniona. KONIEC.";
				break;
			}
			case FIELD_OCCUPIED_EXEPTION:
			{
				std::cout << "Pole zajete -> wybierz inne pole. Podaj wspolrzedne: ";
				break;
			}
			default: break;
			}
			isExeption = true;
		}
	} while (isExeption);
}

bool TicTacToe::graphicPlayerMove(sf::Vector2i polozenieMyszkiWzgledemOkna, sf::RenderWindow & screen)
{

	unsigned int x = (unsigned int)std::floor(size_*polozenieMyszkiWzgledemOkna.x / SCREEN_X);
	unsigned int y = (unsigned int)std::floor(size_*polozenieMyszkiWzgledemOkna.y / SCREEN_Y);

	if (board_->isFieldOccupied(x, y)) return false;

	sf::Texture texture;
	if(player_ == player::O) 
		texture.loadFromFile("Graphics/hand_drawn_circle.png");
	else
		texture.loadFromFile("Graphics/hand_drawn_x.png");
	sf::Sprite sprite;
	sprite.setTexture(texture);

	float scale_x = (float)(SCREEN_X / (float)size_ / SYMBOL_SIZE)-0.5f;
	float scale_y = (float)(SCREEN_Y / (float)size_ / SYMBOL_SIZE)-0.5f;

	float symbol_x = scale_x * SYMBOL_SIZE;
	float symbol_y = scale_y * SYMBOL_SIZE;

	float symbolOrigin_x = SYMBOL_SIZE / 2.f;
	float symbolOrigin_y = SYMBOL_SIZE / 2.f;

	sprite.scale(scale_x,scale_y);
	sprite.setOrigin(symbolOrigin_x, symbolOrigin_y);

	

	board_->mark(player_, x, y);

	scale_x = (float)SCREEN_X / size_ / FIELD_SIZE;
	scale_y = (float)SCREEN_Y / size_ / FIELD_SIZE;

	float symbol_pos_x = FIELD_SIZE * scale_x * (x + 0.5);
	float symbol_pos_y = FIELD_SIZE * scale_y * (y + 0.5);

	sprite.setPosition(symbol_pos_x , symbol_pos_y);
	screen.draw(sprite);
	howManyEmpty_--;
	return true;
}

bool TicTacToe::graphicComputerMove(sf::RenderWindow & screen)
{
	std::vector<unsigned int> vector_x;
	std::vector<unsigned int> vector_y;
	Board currentBoard(*board_);
	unsigned int optimalXY[2] = { 0,0 };
	int maximum = PLAYER_WIN_VALUE;
	int tmp = 0;
	if (howManyEmpty_ > 49) maxDepthLevel_ = 1;
	if (howManyEmpty_ > 25 and howManyEmpty_ <= 49) maxDepthLevel_ = 2;
	if (howManyEmpty_ > 14 and howManyEmpty_ <= 25) maxDepthLevel_ = 3;
	if (howManyEmpty_ > 9 and howManyEmpty_ <= 14) maxDepthLevel_ = 4;
	if (howManyEmpty_ > 5 and howManyEmpty_ <= 9) maxDepthLevel_ = 5;
	if (howManyEmpty_ <= 5) maxDepthLevel_ = 8;
	for (unsigned int x = 0; x < currentBoard.getSize(); x++)
	{
		for (unsigned int y = 0; y < currentBoard.getSize(); y++)
		{

			if (currentBoard.isFieldOccupied(x, y))
				continue;
			Board newBoard(currentBoard);
			newBoard.mark(computer_, x, y);

			tmp = minmax_player(newBoard, 1, PLAYER_WIN_VALUE, COMPUTER_WIN_VALUE);
			std::cout << tmp << std::endl;
			if (tmp == COMPUTER_WIN_VALUE)
			{
				optimalXY[0] = x;
				optimalXY[1] = y;
				break;
			}
			if (tmp == maximum)
			{
				vector_x.push_back(x);
				vector_y.push_back(y);
				optimalXY[0] = x;
				optimalXY[1] = y;
				maximum = tmp;
			}
			if (tmp > maximum)
			{
				vector_x.clear();
				vector_y.clear();
				vector_x.push_back(x);
				vector_y.push_back(y);
				optimalXY[0] = x;
				optimalXY[1] = y;
				maximum = tmp;
			}
			
		}
		if (tmp == COMPUTER_WIN_VALUE) break;
	}
	if(tmp != COMPUTER_WIN_VALUE)
		{
		srand((unsigned int)time(NULL));
		int i = rand() % vector_x.size();
		optimalXY[0] = vector_x[i];
		optimalXY[1] = vector_y[i];
		}
	board_->mark(computer_, optimalXY[0], optimalXY[1]);

	//-----------------------------------------------------------
	sf::Texture texture;
	if (computer_ == player::O)
		texture.loadFromFile("Graphics/hand_drawn_circle.png");
	else
		texture.loadFromFile("Graphics/hand_drawn_x.png");
	sf::Sprite sprite;
	sprite.setTexture(texture);

	float scale_x = (float)(SCREEN_X / (float)size_ / SYMBOL_SIZE) - 0.5f;
	float scale_y = (float)(SCREEN_Y / (float)size_ / SYMBOL_SIZE) - 0.5f;

	float symbol_x = scale_x * SYMBOL_SIZE;
	float symbol_y = scale_y * SYMBOL_SIZE;

	float symbolOrigin_x = SYMBOL_SIZE / 2.f;
	float symbolOrigin_y = SYMBOL_SIZE / 2.f;

	sprite.scale(scale_x, scale_y);
	sprite.setOrigin(symbolOrigin_x, symbolOrigin_y);

	scale_x = (float)SCREEN_X / size_ / FIELD_SIZE;
	scale_y = (float)SCREEN_Y / size_ / FIELD_SIZE;

	float symbol_pos_x = FIELD_SIZE * scale_x * (optimalXY[0] + 0.5);
	float symbol_pos_y = FIELD_SIZE * scale_y * (optimalXY[1] + 0.5);

	sprite.setPosition(symbol_pos_x, symbol_pos_y);
	screen.draw(sprite);
	howManyEmpty_--;
	return true;
}

int TicTacToe::h(Board board)
{
	std::string tmp1(r_ + 1, (char)player_);
	std::string tmp2(r_ + 1, (char)computer_);
	std::string pattern;

	

	pattern = tmp1;
	pattern.front() = ' ';
	pattern.back() = ' ';
	if (board.isPatternInRow(pattern)) return -10;

	pattern[(int)pattern.length() / 2] = ' ';
	if (board.isPatternInRow(pattern)) return -9;
	
	pattern = tmp2;
	pattern.front() = ' ';
	pattern.back() = ' ';
	if (board.isPatternInRow(pattern)) return 10;
	
	pattern[(int)pattern.length() / 2] = ' ';
	if (board.isPatternInRow(pattern)) return 9;

	pattern = tmp1;
	pattern.pop_back();
	pattern.front() = ' ';
	pattern.back() = ' ';
	if (board.isPatternInRow(pattern)) return -8;

	pattern = tmp2;
	pattern.pop_back();
	pattern.front() = ' ';
	pattern.back() = ' ';
	if (board.isPatternInRow(pattern)) return 8;


	return 0;
}

int TicTacToe::h_player(Board board)
{
	std::string pattern(r_ + 1, (char)player_);
	pattern.front() = ' ';
	pattern.back() = ' ';
	if (board.isPatternInRow(pattern)) return -10;
	
	pattern = std::string(r_ + 1, (char)computer_);
	pattern.front() = ' ';
	pattern.back() = ' ';
	if (board.isPatternInRow(pattern)) return 10;

	pattern = std::string(r_, (char)player_);
	pattern.front() = ' ';
	pattern.back() = ' ';
	if (board.isPatternInRow(pattern)) return -8;
	
	pattern = std::string(r_, (char)computer_);
	pattern.front() = ' ';
	pattern.back() = ' ';
	if (board.isPatternInRow(pattern)) return 8;

	pattern = std::string(r_ -1, (char)player_);
	pattern.front() = ' ';
	pattern.back() = ' ';
	if (board.isPatternInRow(pattern)) return -5;

	pattern = std::string(r_ - 1, (char)computer_);
	pattern.front() = ' ';
	pattern.back() = ' ';
	if (board.isPatternInRow(pattern)) return 5;

	return 0;
}

int TicTacToe::h_computer(Board board)
{
	std::string pattern(r_ + 1, (char)player_);
	pattern.front() = ' ';
	pattern.back() = ' ';
	if (board.isPatternInRow(pattern)) return -10;

	pattern = std::string(r_ + 1, (char)computer_);
	pattern.front() = ' ';
	pattern.back() = ' ';
	if (board.isPatternInRow(pattern)) return 10;
	
	pattern = std::string(r_, (char)player_);
	pattern.front() = ' ';
	pattern.back() = ' ';
	if (board.isPatternInRow(pattern)) return -8;
	
	pattern = std::string(r_, (char)computer_);
	pattern.front() = ' ';
	pattern.back() = ' ';
	if (board.isPatternInRow(pattern)) return 8;

	pattern = std::string(r_ - 1, (char)player_);
	pattern.front() = ' ';
	pattern.back() = ' ';
	if (board.isPatternInRow(pattern)) return -5;

	pattern = std::string(r_ - 1, (char)computer_);
	pattern.front() = ' ';
	pattern.back() = ' ';
	if (board.isPatternInRow(pattern)) return 5;

	return 0;
}

TicTacToe::TicTacToe(unsigned int size, unsigned int row)
{
	if (row<0 or row>size)
		throw INVALID_MARKS_IN_ROW_EXEPTION;
	board_ = new Board(size);
	r_ = row;
	size_ = size;
	howManyEmpty_ = size * size;
}

TicTacToe::~TicTacToe()
{
}

