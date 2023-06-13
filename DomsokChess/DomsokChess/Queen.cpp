#include "Queen.h"
#include <iostream>
#include "Board.h"
#define COLOR_WHITE "\033[1;37m"
#define COLOR_BLUE "\033[0;34m"
#define COLOR_RESET "\033[0m"

Queen::Queen(Piece_color piece_color) :
	Figure(piece_color)
{
}

Piece_types Queen::get_type() const
{
	return Piece_types::Queen;
}

void Queen::print_figure()
{
	if (m_piece_color == Piece_color::white)
		std::cout << COLOR_WHITE;
	else
		std::cout << COLOR_BLUE;
	std::cout << "Q";
	std::cout << COLOR_RESET;
}

std::vector<FieldDescriptor> Queen::get_available_moves(FieldDescriptor from_field, Board const* board) const
{
	std::vector<FieldDescriptor> available_moves;
	int current = 1;
	FieldDescriptor current_field;

	//bishop type
	while ((int(from_field.first) + current) < 8 && (from_field.second + current) < 9)
	{
		current_field.first = Diagonals(int(from_field.first) + current);
		current_field.second = from_field.second + current;
		if (board->get_field(current_field) == nullptr)
			available_moves.push_back(current_field);
		else
			break;
		++current;
	}
	current = 1;
	while ((int(from_field.first) + current) < 8 && (from_field.second - current) > 0)
	{
		current_field.first = Diagonals(int(from_field.first) + current);
		current_field.second = from_field.second - current;
		if (board->get_field(current_field) == nullptr)
			available_moves.push_back(current_field);
		else
			break;
		++current;
	}
	current = 1;
	while ((int(from_field.first) - current) >= 0 && (from_field.second - current) > 0)
	{
		current_field.first = Diagonals(int(from_field.first) - current);
		current_field.second = from_field.second - current;
		if (board->get_field(current_field) == nullptr)
			available_moves.push_back(current_field);
		else
			break;
		++current;
	}
	current = 1;
	while ((int(from_field.first) - current) >= 0 && (from_field.second + current) < 9)
	{
		current_field.first = Diagonals(int(from_field.first) - current);
		current_field.second = from_field.second + current;
		if (board->get_field(current_field) == nullptr)
			available_moves.push_back(current_field);
		else
			break;
		++current;
	}
	
	//rook type
	current = 1;
	while ((from_field.second + current) < 9)
	{
		current_field.first = from_field.first;
		current_field.second = from_field.second + current;
		if (board->get_field(current_field) == nullptr)
			available_moves.push_back(current_field);
		else
			break;
		++current;
	}
	current = 1;
	while ((from_field.second - current) > 0)
	{
		current_field.first = from_field.first;
		current_field.second = from_field.second - current;
		if (board->get_field(current_field) == nullptr)
			available_moves.push_back(current_field);
		else
			break;
		++current;
	}
	current = 1;
	while ((int(from_field.first) + current) < 8)
	{
		current_field.first = Diagonals(int(from_field.first) + current);
		current_field.second = from_field.second;
		if (board->get_field(current_field) == nullptr)
			available_moves.push_back(current_field);
		else
			break;
		++current;
	}
	current = 1;
	while ((int(from_field.first) - current) >= 0)
	{
		current_field.first = Diagonals(int(from_field.first) - current);
		current_field.second = from_field.second;
		if (board->get_field(current_field) == nullptr)
			available_moves.push_back(current_field);
		else
			break;
		++current;
	}

	return available_moves;
}

bool  Queen::check_move(FieldDescriptor from_field, FieldDescriptor to_field, Board const* board, Piece_color c_player) const
{
	if (board->get_field(to_field) != nullptr || board->get_field(from_field)->get_color() != c_player)
		return false;
	std::vector<FieldDescriptor> available_moves = get_available_moves(from_field, board);
	return std::find(available_moves.begin(), available_moves.end(), to_field) != available_moves.end();
}

std::vector<FieldDescriptor> Queen::get_available_attacks(Board const* board, FieldDescriptor from_field) const
{
	std::vector<FieldDescriptor> available_attacks;
	FieldDescriptor current_field;
	//bishop type
	int current = 1;

	while ((int(from_field.first) + current) < 8 && (from_field.second + current) < 9)
	{
		current_field.first = Diagonals(int(from_field.first) + current);
		current_field.second = from_field.second + current;
		if (board->get_field(current_field) != nullptr)
		{
			available_attacks.push_back(current_field);
			break;
		}
		++current;
	}
	current = 1;
	while ((int(from_field.first) + current) < 8 && (from_field.second - current) > 0)
	{
		current_field.first = Diagonals(int(from_field.first) + current);
		current_field.second = from_field.second - current;
		if (board->get_field(current_field) != nullptr)
		{
			available_attacks.push_back(current_field);
			break;
		}
		++current;
	}
	current = 1;
	while ((int(from_field.first) - current) >= 0 && (from_field.second - current) > 0)
	{
		current_field.first = Diagonals(int(from_field.first) - current);
		current_field.second = from_field.second - current;
		if (board->get_field(current_field) != nullptr)
		{
			available_attacks.push_back(current_field);
			break;
		}
		++current;
	}
	current = 1;
	while ((int(from_field.first) - current) >= 0 && (from_field.second + current) < 9)
	{
		current_field.first = Diagonals(int(from_field.first) - current);
		current_field.second = from_field.second + current;
		if (board->get_field(current_field) != nullptr)
		{
			available_attacks.push_back(current_field);
			break;
		}
		++current;
	}
	//rook type
	current = 1;
	while ((from_field.second + current) < 9)
	{
		current_field.first = from_field.first;
		current_field.second = from_field.second + current;
		if (board->get_field(current_field) != nullptr)
		{
			available_attacks.push_back(current_field);
			break;
		}
		++current;
	}
	current = 1;
	while ((from_field.second - current) > 0)
	{
		current_field.first = from_field.first;
		current_field.second = from_field.second - current;
		if (board->get_field(current_field) != nullptr)
		{
			available_attacks.push_back(current_field);
			break;
		}
		++current;
	}
	current = 1;
	while ((int(from_field.first) + current) < 8)
	{
		current_field.first = Diagonals(int(from_field.first) + current);
		current_field.second = from_field.second;
		if (board->get_field(current_field) != nullptr)
		{
			available_attacks.push_back(current_field);
			break;
		}
		++current;
	}
	current = 1;
	while ((int(from_field.first) - current) >= 0)
	{
		current_field.first = Diagonals(int(from_field.first) - current);
		current_field.second = from_field.second;
		if (board->get_field(current_field) != nullptr)
		{
			available_attacks.push_back(current_field);
			break;
		}
		++current;
	}

	return available_attacks;
}

bool Queen::check_attack(Board const* board, FieldDescriptor from_field, FieldDescriptor to_field, Piece_color c_active_player) const
{
	if (board->get_field(to_field)->get_color() == c_active_player || board->get_field(from_field)->get_color() != c_active_player)
		return false;
	std::vector<FieldDescriptor> available_attacks = get_available_attacks(board, from_field);
	return std::find(available_attacks.begin(), available_attacks.end(), to_field) != available_attacks.end();
}

bool  Queen::check_type(char c)const
{
	return c == 'Q';
}
