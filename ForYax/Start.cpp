#include "Start.h"

void random_game::start()
{
	mBoard = new random_Board;
	mBoard->main_point();
	while (!mBoard->is_finish()) {
		auto map = mBoard->GetMap();
		mIO.drawBoard(map, mBoard->Get_M_size(), mBoard->Get_N_size());
		mBoard->check_neighbour();
	}
}

void txt_game::start()
{
	this->mBoard = new txt_Board;
	mBoard->main_point();
	while (!mBoard->is_finish()) {
		auto map = mBoard->GetMap();
		mIO.drawBoard(map, mBoard->Get_M_size(), mBoard->Get_N_size());
		mBoard->check_neighbour();
	}
}