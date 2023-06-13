#pragma once
#include "Figure.h"
class Board;

class Pawn : public Figure
{
public:
	Pawn(Piece_color piece_color);
	Piece_types get_type() const override;
	void print_figure() override;
	static bool check_move(FieldDescriptor fd, Board const *board, Piece_color c_player, FieldDescriptor &from_field);
	std::vector<FieldDescriptor> get_available_moves(FieldDescriptor from_field, Board const* board) const override;
	bool check_move(FieldDescriptor from_field, FieldDescriptor to_field, Board const* board, Piece_color c_player) const override;
	std::vector<FieldDescriptor> get_available_attacks(Board const* board, FieldDescriptor from_field) const override;
	bool check_attack(Board const* board, FieldDescriptor from_field, FieldDescriptor to_field, Piece_color c_active_player) const override;
	bool check_type(char c)const override;
	void set_en_passant(bool en_passant);
	bool get_en_passant()const;

private:
	bool mb_en_passant = false;
};