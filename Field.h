#pragma once

#include <vector>


class Field
{
	unsigned size_h;
	unsigned size_w;
	std::vector<std::vector<short>> base_field;

public:
	Field(unsigned size_h = 10, unsigned size_w = 8);

	unsigned get_size_w() const;
	unsigned get_size_h() const;
	std::vector<std::vector<short>> get_base_field() const;
	void add_point(unsigned i, unsigned j);
	void check_line();
	bool block_exist(unsigned i, unsigned j);
};

