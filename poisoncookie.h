#pragma once

class PoisonCookie {
public:
	PoisonCookie();
	PoisonCookie(int size_x, int size_y);
	~PoisonCookie();
	int ** getBoard() { return mBoard; };
	int getX() { return mSizeX; };
	int getY() { return mSizeY; };
	int getPlayer() { return mCurrentPlayer; };
	void restart();
	void printBoard();
	bool isValid(int x, int y);
	bool move(int x, int y, int player);
	void computerMove();
	bool gameOver();
private:
	int mCurrentPlayer;
	int mSizeX, mSizeY;
	int ** mBoard;
};
