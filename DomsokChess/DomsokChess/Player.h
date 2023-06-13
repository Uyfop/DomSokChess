#pragma once
#include "enum_list.h"
#include <string>
#include <iostream>
#include "Board.h"

class Player
{
public:
	Player(Piece_color color);
	void set_color(Piece_color color);
	Piece_color get_color() const;
	virtual std::string make_move(Board const& board) = 0;

private:
	Piece_color m_color;
};
