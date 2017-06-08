#include <stdio.h>
#include <cstdlib>
#include "poisoncookie.h"

PoisonCookie::PoisonCookie()
:mCurrentPlayer(0), mSizeX(8), mSizeY(8) {
	mBoard = new int*[mSizeY];
	for (int y = 0; y < mSizeY; y++) {
		mBoard[y] = new int[mSizeX];
		for (int x = 0; x < mSizeX; x++) {
			mBoard[y][x] = 1;
		}
	}
}

PoisonCookie::PoisonCookie(int size_x, int size_y)
: mCurrentPlayer(0), mSizeX(size_x), mSizeY(size_y) {
	mBoard = new int*[mSizeY];
	for (int y = 0; y < mSizeY; y++) {
		mBoard[y] = new int[mSizeX];
		for (int x = 0; x < mSizeX; x++) {
			mBoard[y][x] = 1;
		}
	}
}

PoisonCookie::~PoisonCookie() {
	for (int y = 0; y < mSizeY; y++) {
		delete [] mBoard[y];
		mBoard[y] = 0;
	}
	delete [] mBoard;
	mBoard = 0;
}

void PoisonCookie::restart() {
	for (int y = 0; y < mSizeY; y++) {
		for (int x = 0; x < mSizeX; x++) {
			mBoard[y][x] = 1;
		}
	}
}

void PoisonCookie::printBoard() {
	for (int y = 0; y < mSizeY; y++) {
		for (int x = 0; x < mSizeX; x++) {
			printf("%d ", mBoard[y][x]);
		}
		printf("\n");
	}
}

bool PoisonCookie::move(int x_in, int y_in, int player) {
	if (!isValid(x_in, y_in))
		return false;
	for (int y = 0; y < mSizeY; y++) {
		for (int x = 0; x < mSizeX; x++) {
			if (y >= y_in && x >= x_in) {
				mBoard[y][x] = 0;
			}
		}
	}
	return true;
}

bool PoisonCookie::isValid(int x, int y) {
	if (x < 0 || y < 0)
		return false;
	if (x > mSizeX || y > mSizeY)
		return false;
	return mBoard[y][x] == 1;
}

void PoisonCookie::computerMove() {
	int x_in = -1;
	int y_in = -1;
	while (!isValid(x_in, y_in)) {
		x_in = rand() % mSizeX;
		y_in = rand() % mSizeY;
	}
	if (x_in == 0 && y_in == 0) {
		if (isValid(1, 0))
			x_in = 1;
		else if (isValid(0, 1))
			y_in = 1;
	}
	for (int y = 0; y < mSizeY; y++) {
		for (int x = 0; x < mSizeX; x++) {
			if (y >= y_in && x >= x_in) {
				mBoard[y][x] = 0;
			}
		}
	}
}

bool PoisonCookie::gameOver() {
	return mBoard[0][0] == 0;
	for (int y = 0; y < mSizeY; y++) {
		for (int x = 0; x < mSizeX; x++) {
			if (y == 0 && x == 0) {
				continue;
			}
			if (mBoard[y][x] == 1) {
				return false;
			}
		}
	}
	return true;
}
