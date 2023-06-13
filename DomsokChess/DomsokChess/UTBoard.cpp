#include "UTBoard.h"

bool UTBoard::TestMate1()
{
	m_figures.clear();
	memset(pole, 0, sizeof(pole));

	place_figure(10, new King(Piece_color::white));
	place_figure(9, new Queen(Piece_color::white));
	place_figure(8, new King(Piece_color::black));

	return is_mate(Piece_color::black);
}

bool UTBoard::TestMate2()
{
	m_figures.clear();
	memset(pole, 0, sizeof(pole));

	place_figure(10, new King(Piece_color::white));
	place_figure(25, new Rook(Piece_color::white));
	place_figure(24, new Rook(Piece_color::white));
	place_figure(8, new King(Piece_color::black));

	return is_mate(Piece_color::black);
}

bool UTBoard::TestPate1()
{
	m_figures.clear();
	memset(pole, 0, sizeof(pole));

	place_figure(0, new King(Piece_color::white));
	place_figure(17, new Queen(Piece_color::black));
	place_figure(10, new King(Piece_color::black));

	return is_pate(Piece_color::white);
}