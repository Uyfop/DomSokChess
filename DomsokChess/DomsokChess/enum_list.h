#pragma once
#include <vector>
#include <string>

enum class Diagonals 
{
	a = 0,
	b,
	c,
	d,
	e,
	f,
	g,
	h
};

enum class Piece_types
{
	None,
	Pawn,
	Rook,
	Bishop,
	Knight,
	Queen,
	King
};

enum class Piece_color
{
	white,
	black
};

typedef std::pair<Diagonals, int> FieldDescriptor;
FieldDescriptor IndexToFieldDescriptor(int index);
int FieldDescriptorToIndex(FieldDescriptor fd);
FieldDescriptor FieldDescriptorFromString(std::string mv);
