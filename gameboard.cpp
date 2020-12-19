#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <unistd.h>
#include "graphics.h"
#include "gameboard.h"

using namespace std;

Board::Board(PoisonCookie * poison)
: mX(poison->getX()), mY(poison->getY()) {
	mPoison = poison;
	mCookies = new Cookie*[mY];
	for (int y = 0; y < mY; y++) {
		mCookies[y] = new Cookie[mX];
		for (int x = 0; x < mX; x++) {
			mCookies[y][x] = Cookie();
		}
	}
}
Board::~Board() {
	for (int y = 0; y < mY; y++) {
		delete [] mCookies[y];
		mCookies[y] = 0;
	}
	delete [] mCookies;
	mCookies = 0;
}

void Board::updateCookies() {
	int ** board = mPoison->getBoard();
	for (int y = 0; y < mY; y++) {
		for (int x = 0; x < mX; x++) {
			mCookies[y][x].mAlive = board[y][x] == 1;
		}
	}
}

void Board::Draw() {
	// Draw the board lines
	glColor3d(1, 82.0/255, 82.0/255); // #FF5252
	for (int i = 0; i <= mX; i++) {
		DrawLine(i, 0, i, mY);
	}
	for (int i = 0; i <= mY; i++) {
		DrawLine(0, i, mX, i);
	}

	//Draw the Poisoned Cookie a different color
	mCookies[0][0].Draw(0, 0, true);

	//Draw cookies
	for (int y = 0; y < mY; y++) {
		for (int x = 0; x < mX; x++) {
			if (x == 0 && y == 0)
				continue;
			mCookies[y][x].Draw(x, y);
		}
	}
}

void Board::Move(int x, int y) {
	mPoison->move(x, y, 0); updateCookies();
}
void Board::Computer() {
	mPoison->computerMove(); updateCookies();
}

Cookie::Cookie()
: mAlive(true) {
	for (int i = 0; i < 3; i++ ) {
		Chip c;
		c.x = ((rand() % 50)+25) / 100.0;
		c.y = ((rand() % 50)+25) / 100.0;
		c.r = .1;
		mChips.push_back(c);
	}
}

void Cookie::Draw(int x, int y, bool poison) {
	if (mAlive) {
		glColor3d(220.0/255, 146.0/255, 71.0/255);
		DrawCircle(x+.5, y+.5, .4, .01);
		if (poison)
			glColor3d(0,.7,0);
		else
			glColor3d(73.0/255, 34.0/255, 4.0/255);
		for (unsigned int i = 0; i < mChips.size(); i++) {
			DrawCircle(x + mChips[i].x, y + mChips[i].y, mChips[i].r, .01);
		}
	}
}
