#pragma once
#include "Player.h"


class Bot : public Player
{
public:
	Bot(Piece_color color);
	std::string make_move(Board const& board) override;

private:

};