#include"Random_board.h"
#include<string>

class IO {
public:
	void drawBoard(map& const board,const size_t& M,const size_t& N);	//���������
	std::string CastState(Cell::State state);		//�������� ����� ������ � ������������ �� ����� ������ ��
};
