#include <iostream>

class Cell {
public:
	enum class State {DEAD, ALIVE, NONE };
	Cell(State state) : m_State(state) {};
	~Cell() {};
	void setStete(State state) { this->m_State = state; }
	void need_to_chage_state() { is_change = true; }
	void change_State(State mstate) {
		if (mstate == Cell::State::ALIVE) { m_State = Cell::State::DEAD; }
		else { m_State = Cell::State::ALIVE; }
	};
	const State& GetState() { return m_State; };
	const bool& current_state_of_change() { return is_change; }
	void made_change() { is_change = false; }
private:
	State m_State;
	bool is_change=false; //если проверка выявит тру,то она сможет поменять m_State на противоположный
};


