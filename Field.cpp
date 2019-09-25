#include "Field.h"

Field::Field(unsigned size_h, unsigned size_w)
{
	this->size_h = size_h;
	this->size_w = size_w;

	//создаём матрицу и заполняем её нулями
	for (size_t i = 0; i < size_h; i++)
	{
		base_field.push_back(std::vector<short>());
		for (size_t j = 0; j < size_w; j++)
		{
			base_field[i].push_back(0);
		}
	}
}

unsigned Field::get_size_w() const
{
	return size_w;
}

unsigned Field::get_size_h() const
{
	return size_h;
}

std::vector<std::vector<short>> Field::get_base_field() const
{
	return base_field;
}

void Field::add_point(unsigned i, unsigned j)
{
	base_field[i][j] = 1;
}

void Field::check_line()
{
	bool is_collapce;
	int i = 0;
	for(auto iter = base_field.begin(); iter != base_field.end() ; iter++ , i++)
	{
		is_collapce = true;

		for (size_t j = 0; j < size_w; j++)
		{
			if (base_field[i][j] != 1)
			{
				is_collapce = false;
				break;
			}
		}
		if (is_collapce)
		{
			base_field.erase(iter);
			base_field.insert(base_field.begin(), std::vector<short>());
			for (size_t j = 0; j < size_w; j++)
			{
				base_field[0].push_back(0);
			}
			return;
		}
	}
}

bool Field::block_exist(unsigned i, unsigned j)
{
	if (i >= size_w || j >= size_h)
	{
		return false;
	}
	return true;
}
