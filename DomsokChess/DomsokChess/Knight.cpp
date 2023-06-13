#include "Knight.h"
#include <iostream>
#include <vector>
#include <string>
#define COLOR_WHITE "\033[1;37m"
#define COLOR_BLUE "\033[0;34m"
#define COLOR_RESET "\033[0m"
#include "Board.h"


Knight::Knight(Piece_color piece_color) :
	Figure(piece_color)
{
}

Piece_types Knight::get_type() const
{
	return Piece_types::Knight;
}

void Knight::print_figure()
{
	if (m_piece_color == Piece_color::white)
		std::cout << COLOR_WHITE;
	else
		std::cout << COLOR_BLUE;
	std::cout << "S";
	std::cout << COLOR_RESET;
}

bool Knight::check_type(char c)const
{
	return c == 'S';
}

std::vector<FieldDescriptor> Knight::get_available_moves(FieldDescriptor from_field, Board const* board) const
{
	std::vector<FieldDescriptor> available_moves;
	int diagonals[] = { -1, 1, -2, 2, -2, 2, -1, 1 };
	int numbers[] = { -2, -2, -1, -1, 1, 1, 2, 2 };

	for (int i = 0; i < 8; i++)
	{
		int dest_diagonal = int(from_field.first) + diagonals[i];
		int dest_number = int(from_field.second) + numbers[i];
		if (dest_diagonal >= 0 && dest_diagonal < 8 && dest_number >= 0 && dest_number < 8 && board->get_field(std::make_pair(Diagonals(dest_diagonal), dest_number)) == nullptr)
			available_moves.push_back(std::make_pair(Diagonals(dest_diagonal), dest_number));
	}
	return available_moves;
}

bool Knight::check_move(FieldDescriptor from_field, FieldDescriptor to_field, Board const* board, Piece_color c_player) const
{
	if (board->get_field(to_field) != nullptr || board->get_field(from_field)->get_color() != c_player)
		return false;
	std::vector<FieldDescriptor> available_moves = get_available_moves(from_field,board);
	return std::find(available_moves.begin(), available_moves.end(), to_field) != available_moves.end();
}

std::vector<FieldDescriptor> Knight::get_available_attacks(Board const* board, FieldDescriptor from_field) const
{
	std::vector<FieldDescriptor> available_attacks;
	FieldDescriptor current_field;
	
	int diagonals[] = { -1, 1, -2, 2, -2, 2, -1, 1 };
	int numbers[] = { -2, -2, -1, -1, 1, 1, 2, 2 };

	for (int i = 0; i < 8; i++)
	{
		current_field.first = Diagonals(int(from_field.first) + diagonals[i]);
		current_field.second = from_field.second + numbers[i];
		if (int(current_field.first) >= 0 && int(current_field.first) < 8 && current_field.second > 0 && current_field.second < 9 && board->get_field(current_field) != nullptr)
			available_attacks.push_back(current_field);
	}
	return available_attacks;
}

bool Knight::check_attack(Board const* board, FieldDescriptor from_field, FieldDescriptor to_field, Piece_color c_active_player) const
{
	if (board->get_field(to_field)->get_color() == c_active_player || board->get_field(from_field)->get_color() != c_active_player)
		return false;
	std::vector<FieldDescriptor> available_attacks = get_available_attacks(board, from_field);
	return std::find(available_attacks.begin(), available_attacks.end(), to_field) != available_attacks.end();
}