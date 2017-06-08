#pragma once
#include <vector>
#include "poisoncookie.h"

struct Chip {
	double x, y, r;
};

class Cookie {
public:
	Cookie();
	~Cookie() {};
	void Draw(int x, int y, bool poison = false);
	bool mAlive;
private:
	std::vector<Chip> mChips;
};

class Board {
public:
	Board(PoisonCookie * poison);
	~Board();
	void updateCookies();
	void Move(int x, int y);
	void Computer();
	void Draw();
private:
	int mX, mY;
	PoisonCookie * mPoison;
	Cookie ** mCookies;
};

