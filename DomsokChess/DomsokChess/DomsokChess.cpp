#include <iostream>
#include "Board.h"
#include "Player.h"
#include "Human.h"
#include "Bot.h"
#include "enum_list.h"
#include "UTBoard.h"

bool human_choose_color(std::vector<Player*> &players, Piece_color &human_color)
{
	players.clear();

	int answer;
	std::cout << "What color do u choose 1:white or 2:black" << std::endl;
	std::cin >> answer;

	if (std::cin.fail())
	{
		std::cin.clear(); 
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input try again" << std::endl;
		return false;
	}

	switch (answer)
	{
	case 1:
	{
		players.push_back(new Human(Piece_color::white));
		players.push_back(new Bot(Piece_color::black));
		human_color = Piece_color::white;
		break;
	}
	case 2:
	{
		players.push_back(new Bot(Piece_color::white));
		players.push_back(new Human(Piece_color::black));
		human_color = Piece_color::black;
		break;
	}
	default:
	{
		std::cout << "Try again" << std::endl;
		return false;
	}
	}	
	return true;
}

bool unittests_passed()
{
	FieldDescriptor test1 = IndexToFieldDescriptor(10);

	if (test1.first != Diagonals::f || test1.second != 2)
	{
		std::cout << "IndexToFieldDescriptor failure!\n";
		return false;
	}

	FieldDescriptor test2 = IndexToFieldDescriptor(0);

	if (test2.first != Diagonals::h || test2.second != 1)
	{
		std::cout << "IndexToFieldDescriptor failure!\n";
		return false;
	}

	UTBoard board;

	if (!board.TestMate1())
	{
		std::cout << "TestMate1 failure!\n";
		return false;
	}

	if (!board.TestMate2())
	{
		std::cout << "TestMate2 failure!\n";
		return false;
	}

	if (!board.TestPate1())
	{
		std::cout << "TestPate1 failure!\n";
		return false;
	}

	return true;
}

int main()
{
	if (!unittests_passed())
		return (-1);
	bool game_ended = false;
	Board board;
	std::vector<Player*> players;
	Piece_color human_color;
	
	while (game_ended == false)
	{
		board.start_board();
		while (!human_choose_color(players, human_color)) {};
		std::cout << "game started"<<std::endl;
		int active_player = 0;
		int round = 1;
		while(true)
		{
			board.print_board(human_color);		
			board.en_passant_reset(players[active_player]->get_color());
			if (board.is_mate(players[active_player]->get_color()))
			{
				std::cout << "Mat" << std::endl;
				break;
			}
			if(board.is_pate(players[active_player]->get_color()))
			{
				std::cout << "Pat" << std::endl;
				break;
			}
			std::string move = players[active_player]->make_move(board);
			while (!board.move_check(move, players[active_player]->get_color()))
				move = players[active_player]->make_move(board);
			++active_player;
			active_player %= 2;
		}
	}
	return 0;
}
