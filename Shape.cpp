#include "Shape.h"

Shape::Shape(polyominos type)
{
	if (type == polyominos::square || type == polyominos::straight)
	{
		switch (type)
		{
		case straight:
			size_h = 4;
			size_w = 1;
			break;
		case square:
			size_w = 2;
			size_h = 2;
			break;
		}
		// заполняем base_shape единичками
		for (size_t i = 0; i < size_w; i++)
		{
			base_shape.push_back(std::vector<short>());
			for (size_t j = 0; j < size_h; j++)
			{
				base_shape[i].push_back(1);
			}
		}
	}
	else
	{
		size_w = 2;
		size_h = 3;
		for (size_t i = 0; i < size_w; i++)
		{
			base_shape.push_back(std::vector<short>());
			for (size_t j = 0; j < size_h; j++)
			{
				base_shape[i].push_back(0);
			}
		}

		//у этих фигур всегда совпадают левые верхние угол:
		base_shape[0][0] = 1;
		base_shape[0][1] = 1; 

		switch (type)
		{
		case L:
			base_shape[0][2] = 1;
			base_shape[1][2] = 1;
			break;
		case T:
			base_shape[0][2] = 1;
			base_shape[1][1] = 1;
			size_w = 3;
			break;
		case S:
			base_shape[1][1] = 1;
			base_shape[1][2] = 1;
			size_w = 3;
			break;
		default:
			exit(1);
		}
	}

}

unsigned Shape::get_size_w() const
{
	return size_w;
}

unsigned Shape::get_size_h() const
{
	return size_h;
}

std::vector<std::vector<short>> Shape::get_base_shape() const
{
	return base_shape;
}
