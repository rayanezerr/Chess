#pragma once
#include "Piece.hpp"
#include "Board.hpp"
using namespace std;
class King : public Piece
{
public:
	King(Position position, Color color) : Piece(position, color) {
		type_ = Type::KING;
	}
	Type getType() const override;
	string getName() const { return "King"; }
	vector<Position> getPossibleMoves(const Board& board) const;
	bool isValidMove(const Position& move, Board& board) const;
	bool isInCheck(const Board& board) const;
	~King() = default;
private:

};
