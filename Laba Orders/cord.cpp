#include "cord.h"

cord::cord(int dx, int dy)
{
	fill(dx, dy);
}

void cord::fill(int dx, int dy)
{
	x = dx;
	y = dy;
}

void cord::Print()
{
	std::cout << x << ' ' << y << '\n';
}
