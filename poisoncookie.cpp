#include "poisoncookie.h"

PoisonCookie::PoisonCookie()
 : size_x(7), size_y(6), amount(4)
{
	board = new int*[size_x];
	for (int i=0;i<size_x; i++)
	{
		board[i] = new int[size_y];
		for (int j=0; j<size_y; j++)
		{
			board[i][j] = 0;
		}
	}
}

PoisonCookie::PoisonCookie(int win_amount)
 : size_x(7), size_y(6), amount(win_amount)
{
	board = new int*[size_x];
	for (int i=0;i<size_x; i++)
	{
		board[i] = new int[size_y];
		for (int j=0; j<size_y; j++)
		{
			board[i][j] = 0;
		}
	}
}

PoisonCookie::PoisonCookie(int xs, int ys)
 : size_x(xs), size_y(ys), amount(4)
{
	board = new int*[size_x];
	for (int i=0;i<size_x; i++)
	{
		board[i] = new int[size_y];
		for (int j=0; j<size_y; j++)
		{
			board[i][j] = 0;
		}
	}
}

PoisonCookie::PoisonCookie(int xs, int ys, int win_amount)
 : size_x(xs), size_y(ys), amount(win_amount)
{
	board = new int*[size_x];
	for (int i=0;i<size_x; i++)
	{
		board[i] = new int[size_y];
		for (int j=0; j<size_y; j++)
		{
			board[i][j] = 0;
		}
	}
}

PoisonCookie::PoisonCookie(const PoisonCookie &game)
{
	*this = game;
}

PoisonCookie &PoisonCookie::operator=(const PoisonCookie &rhs)
{
	this->board = rhs.board;
}

PoisonCookie::~PoisonCookie()
{
	for (int i=0; i<size_x; i++)
	{
		delete [] board[i];
		board[i] = 0;
	}
	delete [] board;
	board = 0;
}

int ** PoisonCookie::getBoard()
{
	return board;
}

int PoisonCookie::getAmount()
{
	return amount;
}

int PoisonCookie::getX()
{
	return size_x;
}

int PoisonCookie::getY()
{
	return size_y;
}

void PoisonCookie::restart()
{
	for (int i=0;i<size_x; i++)
	{
		for (int j=0; j<size_y; j++)
		{
			board[i][j] = 0;
		}
	}
}
	
bool PoisonCookie::makeMove(int column, int player)
{
	if (column > size_x || column < 0)
	{
		return false;
	}
	for (int i = 0; i < size_y; i++)
	{
		if (board[column][i] == 0)
		{
			board[column][i] = player;
			return true;
		}
	}
	return false;
	//check if column is full
	//if not full put piece in column
}

bool PoisonCookie::full()
{
	for (int i = 0; i < size_x; i++)
	{
		for (int j=0; j<size_y; j++)
		{
			if (board[i][j] == 0)
				return false;
		}
	}
	return true;
}

int PoisonCookie::gameOver()
{
	for (int i=0; i<size_x; ++i)
	{
		for (int j=0; j<size_y; j++)
		{
			if (board[i][j] != 0)
			{
				//i max = 7, j max = 6;
				//check if any by ij are the same as ij
				//if so, continue, if not then return 0
				int k = 1;
				for (k=1; k <=amount; k++)
				{
					if (i+k < size_x && board[i][j] == board[i+k][j])
						continue;
					break;
				}
				if (k == amount)
					return board[i][j];
				for (k=1; k <=amount; k++)
				{
					if (i+k < size_x && j+k < size_y && board[i][j] == board[i+k][j+k])
						continue;
					break;
				}
				if (k == amount)
					return board[i][j];
				for (k=1; k <=amount; k++)
				{
					if (j+k < size_y && board[i][j] == board[i][j+k])
						continue;
					break;
				}
				if (k == amount)
					return board[i][j];
				for (k=1; k <=amount; k++)
				{
					if (i-k > 0 && j+k < size_y && board[i][j] == board[i-k][j+k])
						continue;
					break;
				}
				if (k == amount)
					return board[i][j];
			}
		}
		
	}
	if (full())
		return -1;
	return 0;
}
