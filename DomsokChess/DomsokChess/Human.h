#pragma once
#include "Player.h"


class Human : public Player
{
public:
	Human(Piece_color);
	std::string make_move(Board const& board) override;

private:

};