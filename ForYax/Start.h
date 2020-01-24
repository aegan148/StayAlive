#include"IO.h"

class game {
public:
	game() {};
	virtual void start()=0;
	virtual ~game() {};
protected:
	Board* mBoard=nullptr;
	IO mIO;
};

class random_game :public game {
public:
	random_game() {};
	~random_game() { delete mBoard;	};
	void start()override;
};

class txt_game :public game {
public:
	txt_game() {};
	~txt_game() {};
	void start()override;
};