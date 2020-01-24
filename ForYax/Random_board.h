#include <map>
#include<fstream>
#include "Cell.h"

using pos = std::pair<int, int>; //������ ���������� �� �����
using map = std::map<pos, Cell>;// ������ ���������� � �� ���������

class Board {
public:
	Board() {};
	~Board() {};
	virtual void main_point()=0;
	void board_reset();							//��� ����������� �������������������� ����� ���������� ��������� � ��������� ����� ������
	const map & GetMap() { return mCells; }		//���������� ������� �����
	bool check_neighbour();						//��������� ������
	void chek_state_neighbour(pos& temp_pos, size_t& alive);			//� ��� ��������� � �������� ������
	void change_state_cell();						//���� ����� �� ����� ������ � ������ "��������", �� ������ �� ��������������� �����. ���� ����� � cell.h
	const bool& is_finish() { return finish; }		//���� ������ ������,������ ���� ����
	const size_t& Get_M_size() { return M_size; }
	const size_t& Get_N_size() { return N_size; }	
protected:
	bool finish = false;
	size_t M_size = NULL;
	size_t N_size = NULL;
	map mCells;
};

class random_Board: public Board {		//������ ��� ��������� �����
public:
	random_Board() {};
	~random_Board() {};
	void main_point() override;

	void ask_size_board();
	void SetMap();
};

class txt_Board : public Board {	//������ ��� ��� �����
public:
	txt_Board() {};
	~txt_Board() {};
	void main_point() override;

	void ask_create_txt();
	void set_state_cells_txt();
	void Get_state_from_txt();
	void create_the_txt();
	void get_size_from_txt();
	void fill_the_txt(map& mCell);	//�������� ��������� ��� ���������� �� �����
	void eror_txt();		//�������� ��� �������. �������� ��� � ��������� ������
};