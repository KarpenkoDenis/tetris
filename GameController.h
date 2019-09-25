#pragma once

#include "Field.h"
#include "Shape.h"
#include <utility>
#include <time.h>

class GameController
{
	Field main_field;
	Shape curr_shape;
	std::pair<unsigned, unsigned> possition_shape;
	bool can_move();
	void add_shape_to_field();
public:
	GameController();

	void generate_new_shape();
	void move_shape();
	std::vector<std::vector<short>> get_draw_field();
	void move_right();
	void move_left();

public:
	


};

