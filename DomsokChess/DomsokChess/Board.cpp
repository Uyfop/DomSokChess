#include <iostream>
#include <regex>
#include "Board.h"

FieldDescriptor IndexToFieldDescriptor(int index)
{
	return std::make_pair(Diagonals(7 - index%8), index/8 +1);
}

int FieldDescriptorToIndex(FieldDescriptor fd)
{
	//a = 0 b=1 c=2 d=3 e=4 f=5 g=6 h=7 liczba != 1 to wtedy np a 2=8 0+(2-1)*8=8 b2=9 1+(2-1)*8=9 a3=0+(3-1)*8||||||| -48 bo to string 
	int index = 0;
	switch (fd.first)
	{
	case Diagonals::a:
		index += 7;
		break;
	case Diagonals::b:
		index += 6;
		break;
	case Diagonals::c:
		index += 5;
		break;
	case Diagonals::d:
		index += 4;
		break;
	case Diagonals::e:
		index += 3;
		break;
	case Diagonals::f:
		index += 2;
		break;
	case Diagonals::g:
		index += 1;
		break;
	case Diagonals::h:
		index += 0;
		break;
	}
	index += (fd.second - 1) * 8;
	return index;
}

FieldDescriptor FieldDescriptorFromString(std::string mv)
{
	return std::make_pair(Diagonals(mv[0] - 'a'), mv[1] - '0');
}

Piece_types FigureCharToType(char c)
{
	switch (c)
	{
	case'R':
		return Piece_types::Rook;
	case'Q':
		return Piece_types::Queen;
	case'S':
		return Piece_types::Knight;
	case'B':
		return Piece_types::Bishop;
	}
	return Piece_types::None;
}

void Board::place_figure(int pos, Figure *pFigure)
{
	m_figures.push_back(pFigure);
	pole[pos] = pFigure;
}

Figure* generate_figure(Piece_types piece_type, Piece_color color)
{
	switch (piece_type)
	{
	case Piece_types::Rook:
		return new Rook(color);
	case Piece_types::Pawn:
		return new Pawn(color);
	case Piece_types::Bishop:
		return new Bishop(color);
	case Piece_types::Knight:
		return new Knight(color);
	case Piece_types::Queen:
		return new Queen(color);
	case Piece_types::King:
		return new King(color);
	}

	return nullptr;
}

void Board::start_board()
{
	m_figures.clear();
	memset(pole, 0, sizeof(pole));
	/*place_figure(0, new Rook(Piece_color::white));
	place_figure(1, new Knight(Piece_color::white));
	place_figure(2, new Bishop(Piece_color::white));
	place_figure(3, new King(Piece_color::white));
	place_figure(4, new Queen(Piece_color::white));
	place_figure(5, new Bishop(Piece_color::white));
	place_figure(6, new Knight(Piece_color::white));
	place_figure(7, new Rook(Piece_color::white));
	for(int i = 8; i<16; ++i)
		place_figure(i, new Pawn(Piece_color::white));
	place_figure(63, new Rook(Piece_color::black));
	place_figure(62, new Knight(Piece_color::black));
	place_figure(61, new Bishop(Piece_color::black));
	place_figure(60, new Queen(Piece_color::black));
	place_figure(59, new King(Piece_color::black));
	place_figure(58, new Bishop(Piece_color::black));
	place_figure(57, new Knight(Piece_color::black));
	place_figure(56, new Rook(Piece_color::black));
	for (int i = 48; i < 56; ++i)
		place_figure(i, new Pawn(Piece_color::black));
	place_figure(0, new Rook(Piece_color::white));
	place_figure(3, new King(Piece_color::white));
	place_figure(59, new King(Piece_color::black));
	place_figure(7, new Rook(Piece_color::white));
	place_figure(56, new Rook(Piece_color::black));
	place_figure(63, new Rook(Piece_color::black));*/
	place_figure(55, new Rook(Piece_color::white));
	place_figure(0, new King(Piece_color::white));
	place_figure(59, new King(Piece_color::black));
	for (int i = 48; i < 55; ++i)
		place_figure(i, new Pawn(Piece_color::black));

}

void Board::print_board(Piece_color k)
{
	if (k == Piece_color::white)
		for (int i = 63; i >= 0; --i)
		{
			if (pole[i] == nullptr)
				std::cout << "X";
			else
				pole[i]->print_figure();
			if ((i)  % 8 == 0)
				std::cout << std::endl;
		}
	else
		for (int i = 0; i < 64; ++i)
		{
			if (pole[i] == nullptr)
				std::cout << "X";
			else
				pole[i]->print_figure();
			if ((i + 1) % 8 == 0)
				std::cout << std::endl;
		}
}

bool Board::empty_field(int field)
{
	if (pole[field] == nullptr)
		return true;
	return false;
}

Figure* Board::get_field(FieldDescriptor fd) const
{
	return pole[FieldDescriptorToIndex(fd)];
}

std::vector<FieldDescriptor> Board::check_available_moves(Piece_color c_active_player) const
{
	std::vector<FieldDescriptor> all_available_moves;
	std::vector<FieldDescriptor> current_field;
	for (int i = 0; i < 64; ++i)
	{
		Figure* pFigure = get_field(IndexToFieldDescriptor(i));
		if (pFigure->get_color() != c_active_player)
		{
			current_field = pFigure->get_available_moves(IndexToFieldDescriptor(i), this);
			all_available_moves.insert(all_available_moves.end(), current_field.begin(), current_field.end());
		}
	}
	return all_available_moves;
}

std::vector<FieldDescriptor> Board::check_available_attacks(Piece_color c_active_player) const
{
	std::vector<FieldDescriptor> all_available_attacks;
	std::vector<FieldDescriptor> current_field;
	for (int i = 0; i < 64; ++i)
	{
		Figure* pFigure = get_field(IndexToFieldDescriptor(i));
		if (!pFigure)
			continue;
		if (pFigure->get_color() != c_active_player)
		{
			if(pFigure->get_type() != Piece_types::Pawn)
			{
				current_field = pFigure->get_available_moves(IndexToFieldDescriptor(i), this);
				all_available_attacks.insert(all_available_attacks.end(), current_field.begin(), current_field.end());
			}
			current_field = pFigure->get_available_attacks(this,IndexToFieldDescriptor(i));
			all_available_attacks.insert(all_available_attacks.end(), current_field.begin(), current_field.end());
		}
	}
	return all_available_attacks;
}

bool Board::king_is_checked(Piece_color c_active_player) const
{
	std::vector<FieldDescriptor> available_attacks = check_available_attacks(c_active_player);
	for(int i =0; i<64; ++i)
	{
		Figure* pFigure = get_field(IndexToFieldDescriptor(i));
		if (!pFigure)
			continue;
		if (pFigure->get_color() == c_active_player && pFigure->get_type() == Piece_types::King &&
			std::find(available_attacks.begin(), available_attacks.end(), IndexToFieldDescriptor(i)) != available_attacks.end())
			return true;
	}
	return false;
}

bool Board::is_mate(Piece_color c_active_color)
{
	if (!king_is_checked(c_active_color))
		return false;

	std::vector<FieldDescriptor> current_available;
	std::vector<FieldDescriptor> all_current_available;
	Figure* cp_pola[64];
	memcpy(cp_pola, pole, sizeof(cp_pola));
	for (int i = 0; i < 64; ++i)
	{
		Figure* pFigure = get_field(IndexToFieldDescriptor(i));
		if (!pFigure)
			continue;
		if (pFigure->get_color() != c_active_color)
			continue;
		current_available = pFigure->get_available_moves(IndexToFieldDescriptor(i), this);
		all_current_available.insert(all_current_available.end(), current_available.begin(), current_available.end());
		current_available = pFigure->get_available_attacks(this, IndexToFieldDescriptor(i));
		all_current_available.insert(all_current_available.end(), current_available.begin(), current_available.end());

		for (int j = 0; j < all_current_available.size(); ++j)
		{
			std::swap(pole[i], pole[FieldDescriptorToIndex(all_current_available[j])]);
			pole[i] = nullptr;
			bool king_still_checked = king_is_checked(c_active_color);
			memcpy(pole, cp_pola, sizeof(pole));
			if (!king_still_checked)
				return false;
		}
	}
	return true;
}

bool Board::is_pate(Piece_color c_active_color)
{
	std::vector<FieldDescriptor> current_available;
	std::vector<FieldDescriptor> all_current_available;
	Figure* cp_pola[64];
	memcpy(cp_pola, pole, sizeof(cp_pola));
	for (int i = 0; i < 64; ++i)
	{
		Figure* pFigure = get_field(IndexToFieldDescriptor(i));
		if (!pFigure)
			continue;
		if (pFigure->get_color() != c_active_color)
			continue;
		current_available = pFigure->get_available_moves(IndexToFieldDescriptor(i), this);
		all_current_available.insert(all_current_available.end(), current_available.begin(), current_available.end());
		current_available = pFigure->get_available_attacks(this, IndexToFieldDescriptor(i));
		all_current_available.insert(all_current_available.end(), current_available.begin(), current_available.end());
		for (int j = 0; j < all_current_available.size(); ++j)
		{
			std::swap(pole[i], pole[FieldDescriptorToIndex(all_current_available[j])]);
			pole[i] = nullptr;
			bool king_still_checked = king_is_checked(c_active_color);
			memcpy(pole, cp_pola, sizeof(pole));
			if (!king_still_checked)
				return false;
		}
	}
	return true;
}

void Board::pawns_check(Piece_color c_active_player)
{
	std::regex right_answer("[Q,S,B,R,K]");
	if (c_active_player == Piece_color::white)
	{
		for (int i = 56; i < 64; ++i)
		{
			Figure* pFigure = get_field(IndexToFieldDescriptor(i));
			if (!pFigure)
				continue;
			if (pFigure->get_type() == Piece_types::Pawn)
			{
				std::string answer;
				std::cout << "U need to make a promo what Figure do u choose Q,S,R,B?\n";
				while (!(std::regex_search(answer, right_answer))) { std::cin >> answer; };
				place_figure(i, generate_figure(FigureCharToType(answer[0]), c_active_player));
				pFigure = get_field(IndexToFieldDescriptor(i));
				pFigure->set_moved();
			}
		}
	}
	else
	{
		for (int i = 0; i < 9; ++i)
		{
			Figure* pFigure = get_field(IndexToFieldDescriptor(i));
			if (!pFigure)
				continue;
			if (pFigure->get_type() == Piece_types::Pawn)
			{
				std::string answer;
				std::cout << "U need to make a promo what Figure do u choose Q,S,R,B?";
				while (!(std::regex_search(answer, right_answer))) { std::cin >> answer; };
				place_figure(i, generate_figure(FigureCharToType(answer[0]), c_active_player));
				pFigure = get_field(IndexToFieldDescriptor(i));
				pFigure->set_moved();
			}
		}
	}
}

void Board::en_passant_reset(Piece_color c_active_player)
{
	for (int i = 0; i < 64; ++i)
	{
		Figure* pFigure = get_field(IndexToFieldDescriptor(i));
		if (!pFigure)
			continue;
		if (pFigure->get_color() == c_active_player && pFigure->get_type() == Piece_types::Pawn)
		{
			Pawn* pPawn = dynamic_cast<Pawn*>(pFigure);
			pPawn->set_en_passant(false);
		}
	}
}

void Board::en_passant_check(FieldDescriptor from_field, FieldDescriptor to_field)
{

	Figure* pFigure = get_field(to_field);
	if (pFigure->get_color() == Piece_color::white && from_field.second + 2 == to_field.second)
	{
		Pawn* pPawn = dynamic_cast<Pawn*>(pFigure);
		pPawn->set_en_passant(true);
	}
	if (pFigure->get_color() == Piece_color::black && from_field.second - 2 == to_field.second)
	{
		Pawn* pPawn = dynamic_cast<Pawn*>(pFigure);
		pPawn->set_en_passant(true);
	}
}

bool Board::castle_check(FieldDescriptor king_field, FieldDescriptor rook_field, Piece_color c_active_player)
{
	FieldDescriptor current_field;
	current_field.second = king_field.second;
	if (get_field(king_field) == nullptr || get_field(rook_field) == nullptr)
		return false;
	if(int(king_field.first) > int(rook_field.first))
	{
		if (get_field(king_field)->get_type() != Piece_types::King || get_field(rook_field)->get_type() != Piece_types::Rook)
			return false;
		if (get_field(rook_field)->is_moved() != false || get_field(king_field)->is_moved() != false)
			return false;
		current_field.first = Diagonals(int(king_field.first) - 1);
		while (current_field.first != rook_field.first)
		{
			if (get_field(current_field) != nullptr)
				return false;
			std::swap(pole[FieldDescriptorToIndex(king_field)], pole[FieldDescriptorToIndex(current_field)]);
			if (king_is_checked(c_active_player))
				return false;
			std::swap(pole[FieldDescriptorToIndex(current_field)], pole[FieldDescriptorToIndex(king_field)]);
			current_field.first = Diagonals(int(current_field.first) - 1);
		}
		current_field.first = Diagonals(int(king_field.first) - 2);
		std::swap(pole[FieldDescriptorToIndex(king_field)], pole[FieldDescriptorToIndex(current_field)]);
		get_field(current_field)->set_moved();
		current_field.first = Diagonals(int(king_field.first) - 1);
		std::swap(pole[FieldDescriptorToIndex(rook_field)], pole[FieldDescriptorToIndex(current_field)]);
		get_field(current_field)->set_moved();
	}
	else
	{
		if (get_field(king_field)->get_type() != Piece_types::King || get_field(rook_field)->get_type() != Piece_types::Rook)
			return false;
		if (get_field(rook_field)->is_moved() != false || get_field(king_field)->is_moved() != false)
			return false;
		current_field.first = Diagonals(int(king_field.first) + 1);
		while (current_field.first != rook_field.first)
		{
			if (get_field(current_field) != nullptr)
				return false;
			std::swap(pole[FieldDescriptorToIndex(king_field)], pole[FieldDescriptorToIndex(current_field)]);
			if (king_is_checked(c_active_player))
				return false;
			std::swap(pole[FieldDescriptorToIndex(current_field)], pole[FieldDescriptorToIndex(king_field)]);
			current_field.first = Diagonals(int(current_field.first) + 1);
		}
		current_field.first = Diagonals(int(king_field.first) + 2);
		std::swap(pole[FieldDescriptorToIndex(king_field)], pole[FieldDescriptorToIndex(current_field)]);
		get_field(current_field)->set_moved();
		current_field.first = Diagonals(int(king_field.first) + 1);
		std::swap(pole[FieldDescriptorToIndex(rook_field)], pole[FieldDescriptorToIndex(current_field)]);
		get_field(current_field)->set_moved();
	}
	return true;
}

bool Board::move_check(std::string move, Piece_color c_active_player)
{
	std::regex pawnRegex("^[a-h][1-8]");
	std::regex pawnExRegex("^[a-h][1-8][a-h][1-8]");
	std::regex pawnattackRegex("^[a-h][1-8][x][a-h][1-8]");
	std::regex figure_Regex("^[Q,S,B,R,K][a-h][1-8][a-h][1-8]");
	std::regex figureattackRegex("^[S,B,R,Q,K][a-h][1-8][x][a-h][1-8]");
	std::regex pawn_promotion("^[a-h][1,8][S,B,R,Q]");
	std::regex castle_short("^[0][-][0]");
	std::regex castle_long("^[0][-][0][-][0]");

	switch (move.length())
	{
	case 2:
	{

		if (!std::regex_search(move, pawnRegex))
			return false;
		FieldDescriptor to_field = FieldDescriptorFromString(move);
		FieldDescriptor from_field;
		bool can_move  = Pawn::check_move(to_field, this, c_active_player, from_field);
		if (!can_move)
			return false;
		Figure* cp_pola[64];
		memcpy(cp_pola, pole, sizeof(cp_pola));
		std::swap(pole[FieldDescriptorToIndex(from_field)], pole[FieldDescriptorToIndex(to_field)]);
		if (king_is_checked(c_active_player))
		{
			std::cout << "Bad move: king is checked" << std::endl;
			memcpy(pole, cp_pola, sizeof(pole));
			return false;
		}
		en_passant_check(from_field, to_field);
		get_field(to_field)->set_moved();
	}
	break;
	case 3:
	{
		if (std::regex_search(move, castle_short))
		{
			if (castle_check(c_active_player == Piece_color::white ? IndexToFieldDescriptor(3) : IndexToFieldDescriptor(59),
				c_active_player == Piece_color::white ? IndexToFieldDescriptor(0) : IndexToFieldDescriptor(56), c_active_player))
				break;
			else
				return false;
		}
		if (!std::regex_search(move, pawn_promotion))
			return false;
		FieldDescriptor to_field = FieldDescriptorFromString(move.substr(0,2));
		FieldDescriptor from_field;
		from_field.first = to_field.first;
		if ((c_active_player == Piece_color::white) && ((to_field.second - 1) > 0))
			from_field.second = to_field.second - 1;
		else if ((c_active_player == Piece_color::black) && ((to_field.second + 1) < 9))
			from_field.second = to_field.second + 1;
		else
			return false;
		Figure* pFigure = get_field(from_field);
		if (!pFigure)
			return false;
		if (pFigure->get_type() != Piece_types::Pawn)
			return false;
		if (!pFigure->check_move(from_field, to_field, this, c_active_player))
			return false;
		Figure* cp_pola[64];
		memcpy(cp_pola, pole, sizeof(cp_pola));
		std::swap(pole[FieldDescriptorToIndex(from_field)], pole[FieldDescriptorToIndex(to_field)]);
		if (king_is_checked(c_active_player))
		{
			std::cout << "Bad move: king is checked" << std::endl;
			memcpy(pole, cp_pola, sizeof(pole));
			return false;
		}
		place_figure(FieldDescriptorToIndex(to_field), generate_figure(FigureCharToType(move[2]),c_active_player));
		pFigure = get_field(to_field);
		pFigure->set_moved();
	}
	break;
	case 4:
	{
		if (!std::regex_search(move, pawnExRegex))
			return false;
		FieldDescriptor from_field = FieldDescriptorFromString(move.substr(0, 2));
		FieldDescriptor to_field = FieldDescriptorFromString(move.substr(2, 4));
		Figure* pFigure = get_field(from_field);
		if (!pFigure)
			return false;
		if (!pFigure->check_move(from_field, to_field, this, c_active_player))
			return false;
		Figure* cp_pola[64];
		memcpy(cp_pola, pole, sizeof(cp_pola));
		std::swap(pole[FieldDescriptorToIndex(from_field)], pole[FieldDescriptorToIndex(to_field)]);
		if (king_is_checked(c_active_player))
		{
			std::cout << "Bad move: king is checked" << std::endl;
			memcpy(pole, cp_pola, sizeof(pole));
			return false;
		}
		en_passant_check(from_field, to_field);
		pFigure->set_moved();
	}
	break;
	case 5:
	{
		if (std::regex_search(move, castle_long))
		{
			if (castle_check(c_active_player == Piece_color::white ? IndexToFieldDescriptor(3) : IndexToFieldDescriptor(59),
				c_active_player == Piece_color::white ? IndexToFieldDescriptor(7) : IndexToFieldDescriptor(63), c_active_player))
				break;
			else
				return false;
		}
		if (std::regex_search(move, pawnattackRegex))
		{
			FieldDescriptor from_field = FieldDescriptorFromString(move.substr(0, 2));
			FieldDescriptor to_field = FieldDescriptorFromString(move.substr(3, 5));
			Figure* pFigure = get_field(from_field);
			if (!pFigure)
				return false;
			bool can_move = pFigure->check_attack(this, from_field, to_field, c_active_player);
			if (!can_move)
				return false;
			Figure* cp_pola[64];
			memcpy(cp_pola, pole, sizeof(cp_pola));
			if (get_field(to_field) == nullptr)
			{
				if(get_field(from_field)->get_color() == Piece_color::white)
				{
					std::swap(pole[FieldDescriptorToIndex(from_field)], pole[FieldDescriptorToIndex(to_field)]);
					to_field.second -= 1;
					pole[FieldDescriptorToIndex(to_field)] = nullptr;
				}
				else
				{
					std::swap(pole[FieldDescriptorToIndex(from_field)], pole[FieldDescriptorToIndex(to_field)]);
					to_field.second += 1;
					pole[FieldDescriptorToIndex(to_field)] = nullptr;
				}
			}
			else
			{
				std::swap(pole[FieldDescriptorToIndex(from_field)], pole[FieldDescriptorToIndex(to_field)]);
				pole[FieldDescriptorToIndex(from_field)] = nullptr;			
			}
			if (king_is_checked(c_active_player))
			{
				std::cout << "Bad move: king is checked" << std::endl;
				memcpy(pole, cp_pola, sizeof(pole));
				return false;
			}
			pFigure->set_moved();
		}
		else
		{
			if (!std::regex_search(move, figure_Regex))
				return false;
			FieldDescriptor from_field = FieldDescriptorFromString(move.substr(1, 3));
			FieldDescriptor to_field = FieldDescriptorFromString(move.substr(3, 5));
			Figure* pFigure = get_field(from_field);
			if (!pFigure)
				return false;
			if (!pFigure->check_type(move[0]))
				return false;
			if (!pFigure->check_move(from_field, to_field, this, c_active_player))
				return false;
			Figure* cp_pola[64];
			memcpy(cp_pola, pole, sizeof(cp_pola));
			std::swap(pole[FieldDescriptorToIndex(from_field)], pole[FieldDescriptorToIndex(to_field)]);
			if (king_is_checked(c_active_player))
			{
				std::cout << "Bad move: king is checked" << std::endl;
				memcpy(pole, cp_pola, sizeof(pole));
				return false;
			}
			pFigure->set_moved();
		}
	} 
	break;
	case 6:
	{
		if (!std::regex_search(move, figureattackRegex))
			return false;
		FieldDescriptor from_field = FieldDescriptorFromString(move.substr(1, 3));
		FieldDescriptor to_field = FieldDescriptorFromString(move.substr(4, 6));
		Figure* pFigure = get_field(from_field);
		if (!pFigure)
			return false;
		if (!get_field(to_field))
			return false;
		if (!pFigure->check_type(move[0]))
			return false;
		if (!pFigure->check_attack(this, from_field, to_field, c_active_player))
			return false;

		Figure* cp_pola[64];
		memcpy(cp_pola, pole, sizeof(cp_pola));
		std::swap(pole[FieldDescriptorToIndex(from_field)], pole[FieldDescriptorToIndex(to_field)]);
		pole[FieldDescriptorToIndex(from_field)] = nullptr;
		if (king_is_checked(c_active_player))
		{
			std::cout << "Bad move: king is checked" << std::endl;
			memcpy(pole, cp_pola, sizeof(pole));
			return false;
		}
		pFigure->set_moved();
	}
	break;
	default :
	{
		std::cout << "wrong-move\n";
		return false;
	}
	}
	pawns_check(c_active_player);
	if (king_is_checked(c_active_player == Piece_color::white ? Piece_color::black : Piece_color::white))
		std::cout<< "CHECK" <<std::endl;
	return true; 
}