#pragma once
#include "Piece.hpp"
#include <vector>
#include "Board.hpp"

class Bishop : public Piece
{
public:
	Bishop(Position position, Color color) : Piece(position, color) {
		type_ = Type::BISHOP;
	}
	string getName() const { return "Bishop"; }
	Type getType() const override;
	vector<Position> getPossibleMoves(const Board& board) const;
	bool isValidMove(const Position& move, Board& board) const;
	~Bishop() = default;
private:

};

