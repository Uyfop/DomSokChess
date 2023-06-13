#include "King.h"
#include "Board.h"

#define COLOR_WHITE "\033[1;37m"
#define COLOR_BLUE "\033[0;34m"
#define COLOR_RESET "\033[0m"

King::King(Piece_color piece_color) :
	Figure(piece_color)
{
}

Piece_types King::get_type() const
{
	return Piece_types::King;
}

void King::print_figure()
{
	if (m_piece_color == Piece_color::white)
		std::cout << COLOR_WHITE;
	else
		std::cout << COLOR_BLUE;
	std::cout << "K";
	std::cout << COLOR_RESET;
}

std::vector<FieldDescriptor> King::get_available_moves(FieldDescriptor from_field, Board const* board) const
{
	std::vector<FieldDescriptor> available_moves;
	FieldDescriptor current_field;

	int diagonals[] = { -1, 0, 1, 1, 1, 0, -1, -1 };
	int numbers[] = { 1, 1, 1, 0, -1, -1, -1, 0};

	for (int i = 0; i < 8; ++i)
	{
		current_field.first = Diagonals(int(from_field.first) + diagonals[i]);
		current_field.second = from_field.second + numbers[i];
		if (int(current_field.first) >= 0 && int(current_field.first) < 8 && current_field.second > 0 && current_field.second < 9 && board->get_field(current_field) == nullptr)
			available_moves.push_back(current_field);
	}
	return available_moves;
	// tu musze zrobic vector skladajacy sie z wszystkich mozlwiyhc ruchow przeciwnika i odjac te ktore sa w tym wektorze
	// tam petla po boardzie a druga co caly vektor available daje na ten drugi co bedzie suma albo sprawdzam poprostu na zwroconym wektorze czy jest i tyle
	// pozniej po ruchu przeciwnik jezeli krol przeciwnika ma szchowanie true to wtedy sprawdzam czy ma available moves jezeli nie to znaczy ze gra sie konczy
	// oczywiscie gdzies trzeba jeszcze zaznaczyc zaslanianie ale mysle moze ze jak krol dostaje szacha to wtedy jakas dodac do jego available moves czym moze sie zaslonic?!?
	
}

bool King::check_move(FieldDescriptor from_field, FieldDescriptor to_field, Board const* board, Piece_color c_player) const
{
	if (board->get_field(to_field) != nullptr || board->get_field(from_field)->get_color() != c_player)
		return false;
	std::vector<FieldDescriptor> available_moves = get_available_moves(from_field, board);
	return std::find(available_moves.begin(), available_moves.end(), to_field) != available_moves.end();
}

std::vector<FieldDescriptor> King::get_available_attacks(Board const* board, FieldDescriptor from_field) const
{
	std::vector<FieldDescriptor> available_attacks;
	FieldDescriptor current_field;

	int diagonals[] = { -1, 0, 1, 1, 1, 0, -1, -1 };
	int numbers[] = { 1, 1, 1, 0, -1, -1, -1, 0 };

	for (int i = 0; i < 8; ++i)
	{
		current_field.first = Diagonals(int(from_field.first) + diagonals[i]);
		current_field.second = from_field.second + numbers[i];
		if (int(current_field.first) >= 0 && int(current_field.first) < 8 && current_field.second > 0 && current_field.second < 9 && board->get_field(current_field) != nullptr)
			available_attacks.push_back(current_field);
	}
	return available_attacks;
}

bool King::check_attack(Board const* board, FieldDescriptor from_field, FieldDescriptor to_field, Piece_color c_active_player) const
{
	if (board->get_field(to_field)->get_color() == c_active_player || board->get_field(from_field)->get_color() != c_active_player)
		return false;
	std::vector<FieldDescriptor> available_attacks = get_available_attacks(board, from_field);
	return std::find(available_attacks.begin(), available_attacks.end(), to_field) != available_attacks.end();
}

bool King::check_type(char c)const
{
	return c == 'K';
}

bool King::is_checked()const
{
	return mb_checked;
}

void King::toogle_is_checked()
{
	if (mb_checked == true)
		mb_checked = false;
	else
		mb_checked = true;
}