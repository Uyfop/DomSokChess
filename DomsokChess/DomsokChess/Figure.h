#pragma once
#include "enum_list.h"
#include <vector>
#include <iostream>
class Board;

class Figure
{
public:
	Figure(Piece_color piece_color);
	
	virtual Piece_types get_type() const = 0;
	Piece_color get_color() const;
	virtual void print_figure() = 0;
	virtual std::vector<FieldDescriptor> get_available_moves(FieldDescriptor from_field, Board const* board) const = 0;
	virtual bool check_move(FieldDescriptor from_field, FieldDescriptor to_field, Board const* board, Piece_color c_player) const=0;
	virtual std::vector<FieldDescriptor> get_available_attacks(Board const* board, FieldDescriptor from_field) const = 0;
	virtual bool check_attack(Board const* board, FieldDescriptor from_field, FieldDescriptor to_field, Piece_color c_active_player) const = 0;
	bool is_moved() const;
	void set_moved();
	virtual bool check_type(char c)const =0;

protected:
	bool mb_moved = false;
	Piece_color m_piece_color;
};