#include "Figure.h"
#include <iostream>

Figure::Figure(Piece_color piece_color) :
	m_piece_color(piece_color)
{
}

Piece_color Figure::get_color() const
{
	return m_piece_color;
}

bool Figure::is_moved() const
{
	return mb_moved;
}

void Figure::set_moved()
{
	mb_moved = true;
}

