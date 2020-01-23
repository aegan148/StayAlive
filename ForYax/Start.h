#include"IO.h"

class game {
public:
	game() {};
	virtual void start()=0;
	~game() { delete mBoard; };
protected:
	Board* mBoard=nullptr;
	IO mIO;
};

class random_game :public game {
public:
	random_game() {};
	~random_game() { delete mBoard; };
	virtual void start();
};

class txt_game :public game {
public:
	txt_game() {};
	~txt_game() { delete mBoard; };
	virtual void start();
};