#pragma once
#include "Figure.h"
class Board;

class Knight : public Figure
{
public:
	Knight(Piece_color piece_color);
	Piece_types get_type() const override;
	void print_figure() override;
	bool check_move(FieldDescriptor from_field, FieldDescriptor to_field, Board const* board, Piece_color c_player) const override;
	std::vector<FieldDescriptor> get_available_moves(FieldDescriptor from_field, Board const* board) const override;
	std::vector<FieldDescriptor> get_available_attacks(Board const* board, FieldDescriptor from_field) const override;
	bool check_attack(Board const* board, FieldDescriptor from_field, FieldDescriptor to_field, Piece_color c_active_player) const override;
	bool check_type(char c)const override;
private:

};
