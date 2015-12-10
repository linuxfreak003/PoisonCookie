#ifndef _POISONCOOKIE_H_
#define _POISONCOOKIE_H_

class PoisonCookie
{
public:
	PoisonCookie();
	PoisonCookie(int win_amount);
	PoisonCookie(int xs, int ys);
	PoisonCookie(int xs, int ys, int win_amount);
	PoisonCookie(const PoisonCookie &game);
	PoisonCookie &operator=(const PoisonCookie &rhs);
	~PoisonCookie();
	int ** getBoard();
	int getAmount();
	int getX();
	int getY();
	void restart();
	
	bool makeMove(int column, int player);
	bool full();
	int gameOver();
	
protected:
	int active_player;
	int ** board;
	int amount;
	int size_x;
	int size_y;
};


#endif /* _POISONCOOKIE_H_ */
