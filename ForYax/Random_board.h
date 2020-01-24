#include <map>
#include<fstream>
#include "Cell.h"

using pos = std::pair<int, int>; //храним координату на доске
using map = std::map<pos, Cell>;// храним координату и ее состояние

class Board {
public:
	Board() {};
	~Board() {};
	virtual void main_point()=0;
	void board_reset();							//при обнаружении скомпрометированного файла сбрасываем настройки и заполняем файлы заново
	const map & GetMap() { return mCells; }		//возвращаем готовую доску
	bool check_neighbour();						//проверяем соседа
	void chek_state_neighbour(pos& temp_pos, size_t& alive);			//и его положение в обществе клеток
	void change_state_cell();						//если видим на доске клетку с флагом "изменить", то меняем на противоположный стейт. флаг лежит в cell.h
	const bool& is_finish() { return finish; }		//если нечего менять,значит гейм овер
	const size_t& Get_M_size() { return M_size; }
	const size_t& Get_N_size() { return N_size; }	
protected:
	bool finish = false;
	size_t M_size = NULL;
	size_t N_size = NULL;
	map mCells;
};

class random_Board: public Board {		//логика для рандомной доски
public:
	random_Board() {};
	~random_Board() {};
	void main_point() override;

	void ask_size_board();
	void SetMap();
};

class txt_Board : public Board {	//логика для тхт доски
public:
	txt_Board() {};
	~txt_Board() {};
	void main_point() override;

	void ask_create_txt();
	void set_state_cells_txt();
	void Get_state_from_txt();
	void create_the_txt();
	void get_size_from_txt();
	void fill_the_txt(map& mCell);	//посылаем структуру для заполнения из файла
	void eror_txt();		//вызываем при ошибках. обнуляем все и заполняем заново
};