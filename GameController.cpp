#include "GameController.h"

bool GameController::can_move()
{
	const auto base_shape = curr_shape.get_base_shape();
	const auto base_field = main_field.get_base_field();


	for (size_t i = 0; i < base_shape.size(); i++)
	{
		for (size_t j = 0; j < base_shape[0].size(); j++)
		{
			//проверка выхода за пределы матрицы
			if (!main_field.block_exist(possition_shape.first + i, possition_shape.second + j))
			{
				return false;
			}

			// если и там и там клетка занята, то значит двигаться сюда нельзя
			if (base_shape[i][j] == 1 &&
				base_field[possition_shape.second + j][possition_shape.first + i] == 1)
			{
				return false;
			}
		}
	}
	return true;
}

void GameController::add_shape_to_field()
{
	const auto base_shape = curr_shape.get_base_shape();
	for (size_t i = 0; i < base_shape.size(); i++)
	{
		for (size_t j = 0; j < base_shape[0].size(); j++)
		{
			if (base_shape[i][j] == 1)
			{
				main_field.add_point(possition_shape.second + j, possition_shape.first + i);
			}
		}
	}
	//for (size_t i = 0; i < curr_shape.get_size_w(); i++)
	//{

	//	for (size_t j = 0; j < curr_shape.get_size_h(); j++)
	//	{
	//		//проверка выхода за пределы матрицы
	//		//if (main_field.block_exist(possition_shape.second + i, possition_shape.second + j))
	//		//{
	//		//	exit(2); //теоретически эта функция должна вызываться когда пределы уже проверены, поэтому это исключительная ситуация
	//		//}
	//		// если и там и там клетка занята, то значит двигаться сюда нельзя
	//		if (base_shape[i][j] == 1)
	//		{
	//			main_field.add_point(possition_shape.second + i, possition_shape.first + j);
	//		}
	//	}
	//}
	main_field.check_line();
}

GameController::GameController()
{
	generate_new_shape();
}

void GameController::generate_new_shape()
{
	// выбираем рандомный тип фигуры:
	srand(time(NULL));
	unsigned r = rand() % 4;
	curr_shape = Shape(static_cast<polyominos>(rand() % 4));

	// задаём новую стартовую позицию: 
	possition_shape = std::pair<unsigned, unsigned>( main_field.get_size_w() / 2, 1);

	
		
}

void GameController::move_shape()
{
	possition_shape.second = possition_shape.second + 1;
	if (!can_move())
	{
		possition_shape.second = possition_shape.second - 1;
		add_shape_to_field();
		generate_new_shape();
		main_field.check_line();
	}
}

std::vector<std::vector<short>> GameController::get_draw_field()
{
	std::vector<std::vector<short>> base_shape = curr_shape.get_base_shape();
	std::vector<std::vector<short>> base_field = main_field.get_base_field();
	for (size_t i = 0; i < base_shape.size(); i++)
	{
		for (size_t j = 0; j < base_shape[0].size(); j++)
		{
			if (base_shape[i][j] == 1 )
			{
				base_field[possition_shape.second + j][possition_shape.first + i] = 1;
			}
		}
	}

	return base_field;
}

void GameController::move_right()
{
	possition_shape.first = possition_shape.first + 1;
	if (!can_move())
	{
		possition_shape.first = possition_shape.first - 1;
	}
}

void GameController::move_left()
{
	possition_shape.first = possition_shape.first - 1;
	if (!can_move())
	{
		possition_shape.first = possition_shape.first + 1;
	}
}
