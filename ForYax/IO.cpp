#include "IO.h"
#include"windows.h"

void IO::drawBoard(map& const board,const size_t& M,const size_t& N)
{
	Sleep(1000);
	system("cls");
	for (size_t i = 0; i < M; i++) {
		std::cout << "|";
		for (size_t j = 0; j < N; j++) {
			std::cout << CastState(board.at(pos(i, j)).GetState());
			std::cout << "|";
		}
		std::cout << std::endl;
	}
}

std::string IO::CastState(Cell::State state)
{
	std::string result("");
	switch (state)
	{
	case Cell::State::DEAD :
		result = "0";
		break;
	case Cell::State::ALIVE :
		result = "1";
		break;
	default:
		result = "E";//sm error
		break;
	}
	return std::move(result);
}