#include "Human.h"

Human::Human(Piece_color color) :
	Player(color)
{
}

std::string Human::make_move(Board const& board)
{
	std::string move;
	std::cin >> move;
	return move;
}

