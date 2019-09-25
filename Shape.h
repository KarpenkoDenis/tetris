#pragma once
#include <vector>

enum polyominos
{
	straight,
	square,
	L,
	T,
	S
};

class Shape
{
	unsigned size_w;
	unsigned size_h;
	std::vector<std::vector<short>> base_shape;
public:
	Shape(polyominos type = polyominos::T);

	unsigned get_size_w() const;
	unsigned get_size_h() const;
	std::vector<std::vector<short>> get_base_shape() const;
};

