#include "Player.h"

Player::Player(Piece_color color) :
	m_color(color)
{
}

void Player::set_color(Piece_color color)
{
	m_color = color;
}

Piece_color Player::get_color() const
{
	return m_color;
}