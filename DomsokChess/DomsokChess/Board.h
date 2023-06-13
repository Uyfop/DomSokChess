#pragma once
#include "enum_list.h"
#include "Figure.h"
#include "Queen.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "King.h"
#include "Pawn.h"
#include <vector>
#include <string>

class Board
{
public:
	void start_board();
	void print_board(Piece_color k);
	bool move_check(std::string move, Piece_color c_active_player);
	std::vector<FieldDescriptor> check_available_moves(Piece_color c_active_player) const;
	std::vector<FieldDescriptor> check_available_attacks(Piece_color c_active_player) const;
	bool king_is_checked(Piece_color c_active_player) const;
	bool is_mate(Piece_color c_active_color);
	bool is_pate(Piece_color c_active_color);
	void en_passant_reset(Piece_color c_active_player);
	void en_passant_check(FieldDescriptor from_field, FieldDescriptor to_field);
	void pawns_check(Piece_color c_active_player);
	bool empty_field(int field);
	bool castle_check(FieldDescriptor king_field, FieldDescriptor rook_field, Piece_color c_active_color);
	Figure* get_field(FieldDescriptor fd) const;

protected:
	Figure *pole[64];
	std::vector<Figure*> m_figures;
	void place_figure(int pos, Figure *pFigure);
};

