#include "Random_board.h"
#include<ctime>

void Board::board_reset()
{
	this->M_size = NULL;
	this->N_size = NULL;
	this->mCells.clear();
	bool finish = false;
}

void random_Board::main_point()
{
	ask_size_board();
	SetMap();
}

void random_Board::ask_size_board()
{
	std::cout << "Enter a new size of board\n";
	int M_size, N_size;
	std::cout << "Enter M (size of col): 1-10\n";
	while (!(std::cin >> M_size) || (std::cin.peek() != '\n') || (M_size < 1) || (M_size > 10)) {
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << "Error!Reenter M size: (1-10)\n";
	};
	this->M_size = M_size;
	std::cout << "Enter N (size of col): 1-10\n";
	while (!(std::cin >> N_size) || (std::cin.peek() != '\n') || (N_size < 1) || (N_size > 10)) {
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << "Error!Reenter N size: (1-10)\n";
	};
	this->N_size = N_size;
}

void random_Board::SetMap()
{
	srand(time(0));
	for (size_t i = 0; i < M_size; i++) {
		for (size_t j = 0; j < N_size; j++) {
			size_t temp_choose = 0;
			Cell::State state = Cell::State::NONE; 
			temp_choose=rand() % 10;			//подбрасываем игральную кость
			if (temp_choose % 2 == 0) {
				state = Cell::State::ALIVE;
			}
			else {
				state = Cell::State::DEAD;
			}
			pos Position = pos(i, j);		//определились с координатой
			Cell  cells = Cell(state);		//определились с состоянием
			mCells.insert({ std::move(Position), std::move(cells) });		//добавили в  --> std::map<pos, Cell>
		}
	}
}


void txt_Board::main_point()
{
	ask_create_txt();
}

void txt_Board::ask_create_txt()
{
	char local_ansver;
	std::cout << "Do you want to create a new .txt file (1-yes,0-no)? No, if you already made it and I'll check it\n";
	std::cin >> local_ansver;
	if (local_ansver == '1') {
		create_the_txt();
	}
	else {
		get_size_from_txt();
	}
}

void txt_Board::set_state_cells_txt()
{
	int State;

	for (size_t i = 0; i < M_size; i++) {
		for (size_t j = 0; j < N_size; j++) {
			Cell::State mState = Cell::State::NONE;
			std::cout << "Enter the state of Cell: 0-Dead, 1- Alive\n";
			while (!(std::cin >> State) || (std::cin.peek() != '\n') || (State < 0) || (State > 1))
			{
				std::cin.clear();
				while (std::cin.get() != '\n');
				std::cout << "Error!Reenter N size: (0-1)\n";
			};
			if (State == 0) {
				mState = Cell::State::DEAD;
			}
			else if (State == 1) {
				mState = Cell::State::ALIVE;
			}
			pos Position = pos(i, j);		//определились с координатой
			Cell  cells = Cell(mState);		//определились с состоянием
			mCells.insert({ std::move(Position), std::move(cells) });		//добавили в  --> std::map<pos, Cell>
		}
	}
	fill_the_txt(mCells);		// после проведения всех обработок записываем мапу в файл
}

void txt_Board::Get_state_from_txt()
{
	int x = NULL;
	int y = NULL;
	int state = NULL;
	bool file_empty = true;
	Cell::State mState = Cell::State::NONE;
	std::ifstream cell_state_txt;
	cell_state_txt.open("file.txt",std::ios_base::in);
	if (!cell_state_txt) { 
		std::cout << "Can't open file\n";
		eror_txt();
		cell_state_txt.open("file.txt", std::ios_base::in);
		if (!cell_state_txt) { std::cout << "Critical eror\n"; }
	}
	while (cell_state_txt >> x >> y >> state) {
		file_empty = false;
		if ((x >= M_size|| x < 0) || (y >= N_size|| y < 0) || (state > 1 || state < 0)) {
			cell_state_txt.close();
			eror_txt();
			break;
		}
		pos position = pos(x, y);
		if (state == 0) {
			mState = Cell::State::DEAD;
		}
		else if (state == 1) {
			mState = Cell::State::ALIVE;
		}
		Cell mCell = mState;
		mCells.insert({ std::move(position), std::move(mCell) });
	}
	if (file_empty) {
		std::cout << "File is empty!\n";
	}
	cell_state_txt.close();
}

void txt_Board::create_the_txt()
{
	std::cout << "Enter a new size of board\n";
		int M_size,N_size;
		std::cout << "Enter M (size of col): 1-10\n";
		while (!(std::cin >> M_size) || (std::cin.peek() != '\n')|| (M_size<1) || (M_size>10))
		{
			std::cin.clear();
			while (std::cin.get() != '\n');
			std::cout << "Error!Reenter M size: (1-10)\n";
		};
		this->M_size = M_size;
		std::cout << "Enter N (size of col): 1-10\n";
		while (!(std::cin >> N_size) || (std::cin.peek() != '\n') || (N_size < 1) || (N_size > 10))
		{
			std::cin.clear();
			while (std::cin.get() != '\n');
			std::cout << "Error!Reenter N size: (1-10)\n";
		};
		this->N_size = N_size;

		//записали в отдельный файл размеры доски
		std::ofstream txt_for_size_board;
		txt_for_size_board.open("size.txt", std::ios_base::trunc);
		if (!txt_for_size_board) { std::cout << "File error - can't open to write size of board!"; }
		txt_for_size_board << M_size << " " << N_size;
		txt_for_size_board.close();
		std::cout <<"Size_Board file was created!\n"<< std::endl;
		set_state_cells_txt();
}

void txt_Board::get_size_from_txt()
{
	size_t size_M_txt = NULL;
	size_t size_N_txt = NULL;
	std::ifstream size_board_txt;
	size_board_txt.open("size.txt", std::ios_base::in);
	if (!size_board_txt) {	std::cout << "Can't open size file\n";	}
	while (size_board_txt >> size_M_txt >> size_N_txt) {
		this->M_size = size_M_txt;
		this->N_size = size_N_txt;
	}
	Get_state_from_txt();
}

void txt_Board::fill_the_txt(map& mCell)
{
	std::ofstream txt_for_cells;
	txt_for_cells.open("file.txt",std::ios_base::trunc);
	if (!txt_for_cells) {
		std::cout << "File error - can't open to write data!";
	};
	
	for (auto it = mCell.begin(); it != mCell.end(); ++it)
	{
		txt_for_cells << it->first.first << " "<< it->first.second<<" " << (int)it->second.GetState() << "\n";
	}
	txt_for_cells.close();
	std::cout << "Done!" << std::endl;
	Get_state_from_txt();
}

void txt_Board::eror_txt()
{
	std::cout << "Eror. Please fill all the files again\n";
	board_reset();
	create_the_txt();
}

bool Board::check_neighbour()
{
	bool local_finish = true; // если не было изменений в клетках,то значит все на этом кончается
	size_t count_alive = 0;// подсчет живых соседей
	for (size_t i = 0; i < M_size; i++) {
		for (size_t j = 0; j < N_size; j++) {
			count_alive = 0;
			pos current_pos = pos(i, j);//текущая позицмя

			//пробегаемся по всем возможным соседям
			pos right = pos(i, j+1);
			pos t_right = pos(i-1, j + 1);
			pos b_right = pos(i + 1, j + 1);
			pos left = pos(i, j - 1);
			pos t_left = pos(i - 1, j - 1);
			pos b_left = pos(i + 1, j - 1);
			pos top = pos(i - 1, j);//
			pos bottom = pos(i + 1, j);//
				//проверка выхода за рамки.  Если не выходим то запускаем проверку соседа относительно текущей позиции
				if (right.second < N_size) {			//chek board of rigth neighbour
					chek_state_neighbour(right, count_alive);
				}
				if (t_right.first >=0 && t_right.second < N_size)			//chek board of top rigth neighbour
				{
					chek_state_neighbour(t_right, count_alive);
				}
				if (b_right.first <M_size && b_right.second < N_size) {
					chek_state_neighbour(b_right, count_alive);
				}
				if (left.second >= 0) {
					chek_state_neighbour(left, count_alive);
				}
				if (t_left.first >=0 && t_left.second >= 0) {
					chek_state_neighbour(t_left, count_alive);
				}
				if (b_left.first < M_size && b_left.second >= 0) {
					chek_state_neighbour(b_left, count_alive);
				}
				if (top.first >= 0) {
					chek_state_neighbour(top, count_alive);
				}
				if (bottom.first < M_size) {
					chek_state_neighbour(bottom, count_alive);
				}

				//после проверки соседей проверяемя главные условия
				auto current_Cell = mCells.at(current_pos).GetState();
				if (current_Cell == Cell::State::ALIVE) {
					if (count_alive < 2) {
						mCells.at(current_pos).need_to_chage_state();		//поставим флаг,что нужно изменить значение
						local_finish = false;
					}
					else if (count_alive > 3) {
						mCells.at(current_pos).need_to_chage_state();		//поставим флаг,что нужно изменить значение
						local_finish = false;
					}
				}
				if (current_Cell == Cell::State::DEAD &&count_alive==3) {
				mCells.at(current_pos).need_to_chage_state();		//поставим флаг,что нужно изменить значение
				local_finish = false;
				}
		}
	}
	if (!local_finish) { //определились где делаем изменения и теперь меняем их состояние
		change_state_cell();}
	else { finish = true; }
	return finish;
}

void Board::chek_state_neighbour(pos& temp_pos, size_t& alive)
{
	switch (mCells.at(temp_pos).GetState()) {
	case Cell::State::ALIVE:
		alive++;
		break;
	}
}

void Board::change_state_cell()
{
	for (size_t i = 0; i < M_size; i++) {
		for (size_t j = 0; j < N_size; j++) {
			pos pos_for_change = pos(i, j);
			if (mCells.at(pos_for_change).current_state_of_change()) {								//если видим флаг"изменить" ,то меняем значение клетки
				mCells.at(pos_for_change).change_State(mCells.at(pos_for_change).GetState());		 //меняем
				mCells.at(pos_for_change).made_change();											// ставим флаг в обратное положение
			}
		}
	}
}
