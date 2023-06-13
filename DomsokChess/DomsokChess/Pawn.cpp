#include "Pawn.h"
#include <iostream>
#include "Board.h"
#define COLOR_WHITE "\033[1;37m"
#define COLOR_BLUE "\033[0;34m"
#define COLOR_RESET "\033[0m"

Pawn::Pawn(Piece_color piece_color) :
	Figure(piece_color)
{
}

Piece_types Pawn::get_type() const
{
	return Piece_types::Pawn;
}

void Pawn::print_figure()
{
	if (m_piece_color == Piece_color::white)
		std::cout << COLOR_WHITE;
	else
		std::cout << COLOR_BLUE;
	std::cout << "P";
	std::cout << COLOR_RESET;
}

bool Pawn::get_en_passant()const
{
	return mb_en_passant;
}

bool Pawn::check_type(char c)const
{
	return c == 'P';
}

bool Pawn::check_move(FieldDescriptor fd, Board const *board, Piece_color c_player, FieldDescriptor &fd2)
{
	if (board->get_field(fd) != nullptr)
		return false;

	if (c_player == Piece_color::white)
	{
		if (!(fd.second > 2))
			return false;
		fd2 = FieldDescriptor(fd.first, fd.second-1);
		if (board->get_field(fd2) != nullptr)
		{
			if (board->get_field(fd2)->get_type() == Piece_types::Pawn && board->get_field(fd2)->get_color() == c_player)
				return true;
			return false;
		}
		if (!(fd.second > 3))
			return false;
		fd2.second = fd.second-2;
		if (board->get_field(fd2) == nullptr)
			return false;
		if (board->get_field(fd2)->get_type() == Piece_types::Pawn && board->get_field(fd2)->get_color() == c_player && board->get_field(fd2)->is_moved() == false)
			return true;
	}
	else
	{
		if (!(fd.second < 7))
			return false;

		fd2 = FieldDescriptor(fd.first, fd.second + 1);
		if (board->get_field(fd2) != nullptr)
		{
			if (board->get_field(fd2)->get_type() == Piece_types::Pawn && board->get_field(fd2)->get_color() == c_player)
				return true;
			return false;
		}
		if (!(fd.second < 6))
			return false;
		fd2.second = fd.second + 2;
		if (board->get_field(fd2) == nullptr)
			return false;
		if (board->get_field(fd2)->get_type() == Piece_types::Pawn && board->get_field(fd2)->get_color() == c_player && board->get_field(fd2)->is_moved() == false)
			return true;
	}
	return false;
}

std::vector<FieldDescriptor> Pawn::get_available_moves(FieldDescriptor from_field, Board const* board) const
{
	std::vector<FieldDescriptor> available_moves;
	if(board->get_field(from_field)->get_color() == Piece_color::white)
	{
		if((from_field.second +1) <= 8)
			available_moves.push_back({ from_field.first,from_field.second + 1 });
		if (board->get_field(from_field)->is_moved() == false)
			available_moves.push_back({ from_field.first, from_field.second + 2 });
	}
	else
	{
		if ((from_field.second - 1) >= 0)
			available_moves.push_back({ from_field.first,from_field.second + -1 });
		if (board->get_field(from_field)->is_moved() == false)
			available_moves.push_back({ from_field.first, from_field.second - 2 });
	}
	return available_moves;
}

bool Pawn::check_move(FieldDescriptor from_field, FieldDescriptor to_field, Board const* board, Piece_color c_player) const
{
	if (board->get_field(to_field) != nullptr || board->get_field(from_field)->get_color() != c_player)
		return false;
	std::vector<FieldDescriptor> available_moves = get_available_moves(from_field, board);
	return std::find(available_moves.begin(), available_moves.end(), to_field) != available_moves.end();
}

std::vector<FieldDescriptor> Pawn::get_available_attacks(Board const* board, FieldDescriptor from_field) const
{
	std::vector<FieldDescriptor> available_attacks;
	FieldDescriptor current_field;
	Figure* pFigure = board->get_field(from_field);
	if (pFigure)
	{
		if (pFigure->get_color() == Piece_color::white)
		{
			current_field.first = Diagonals(int(from_field.first) - 1);
			current_field.second = from_field.second + 1;
			if (int(current_field.first) >= 0 && current_field.second <= 8 && board->get_field(current_field) != nullptr && board->get_field(current_field)->get_color() != pFigure->get_color())
				available_attacks.push_back(current_field);
			current_field.first = Diagonals(int(from_field.first) + 1);
			if (int(current_field.first) <= 7 && current_field.second <= 8 && board->get_field(current_field) != nullptr && board->get_field(current_field)->get_color() != pFigure->get_color())
				available_attacks.push_back(current_field);
			current_field.second = from_field.second;
			Figure* pFigure_target = board->get_field(current_field);
			if (int(current_field.first) <= 7 && current_field.second < 8 && board->get_field(current_field) != nullptr &&
				pFigure_target->get_color() != pFigure->get_color() && pFigure_target->get_type() == Piece_types::Pawn)
			{
				Pawn* pPawn_target = dynamic_cast<Pawn*>(pFigure_target);
				current_field.second += 1;
				if(pPawn_target->get_en_passant() == true && board->get_field(current_field) == nullptr) 
					available_attacks.push_back(current_field);
			}
			current_field.second = from_field.second;
			current_field.first = Diagonals(int(from_field.first) - 1);
			pFigure_target = board->get_field(current_field);
			if (int(current_field.first) >= 0 && current_field.second < 8 && board->get_field(current_field) != nullptr &&
				pFigure_target->get_color() != pFigure->get_color() && pFigure_target->get_type() == Piece_types::Pawn)
			{
				Pawn* pPawn_target = dynamic_cast<Pawn*>(pFigure_target);
				current_field.second += 1;
				if (pPawn_target->get_en_passant() == true && board->get_field(current_field) == nullptr)
					available_attacks.push_back(current_field);
			}
		}
		else
		{
			current_field.first = Diagonals(int(from_field.first) - 1);
			current_field.second = from_field.second - 1;
			if (int(current_field.first) >= 0 && current_field.second >= 0 && board->get_field(current_field) != nullptr && board->get_field(current_field)->get_color() != pFigure->get_color())
				available_attacks.push_back(current_field);
			current_field.first = Diagonals(int(from_field.first) + 1);
			if (int(current_field.first) <= 7 && current_field.second >= 0 && board->get_field(current_field) != nullptr && board->get_field(current_field)->get_color() != pFigure->get_color())
				available_attacks.push_back(current_field);
			
			current_field.second = from_field.second;
			Figure* pFigure_target = board->get_field(current_field);
			if (int(current_field.first) <= 7 && current_field.second > 0 && board->get_field(current_field) != nullptr &&
				pFigure_target->get_color() != pFigure->get_color() && pFigure_target->get_type() == Piece_types::Pawn)
			{
				Pawn* pPawn_target = dynamic_cast<Pawn*>(pFigure_target);
				current_field.second -= 1;
				if (pPawn_target->get_en_passant() == true && board->get_field(current_field) == nullptr)
					available_attacks.push_back(current_field);
			}
			current_field.second = from_field.second;
			current_field.first = Diagonals(int(from_field.first) - 1);
			pFigure_target = board->get_field(current_field);
			if (int(current_field.first) >= 0 && current_field.second > 0 && board->get_field(current_field) != nullptr &&
				pFigure_target->get_color() != pFigure->get_color() && pFigure_target->get_type() == Piece_types::Pawn)
			{
				Pawn* pPawn_target = dynamic_cast<Pawn*>(pFigure_target);
				current_field.second -= 1;
				if (pPawn_target->get_en_passant() == true && board->get_field(current_field) == nullptr)
					available_attacks.push_back(current_field);
			}
		}
	}
	return available_attacks;
}

bool Pawn::check_attack(Board const* board, FieldDescriptor from_field, FieldDescriptor to_field, Piece_color c_active_player) const
{
	if (board->get_field(to_field) != nullptr && (board->get_field(to_field)->get_color() == c_active_player || board->get_field(from_field)->get_color() != c_active_player))
		return false;
	std::vector<FieldDescriptor> available_attacks = get_available_attacks(board, from_field);
	return std::find(available_attacks.begin(), available_attacks.end(), to_field) != available_attacks.end();
}

void Pawn::set_en_passant(bool en_passant)
{
	mb_en_passant = en_passant;
}