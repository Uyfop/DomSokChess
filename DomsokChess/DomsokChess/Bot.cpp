#include "Bot.h"

Bot::Bot(Piece_color color) :
	Player(color)
{
}

std::string Bot::make_move(Board const& board)
{
	std::string move;
	std::cin >> move;
	return move;
}