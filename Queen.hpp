#pragma once
#include "Piece.hpp"
#include <vector>
#include "Board.hpp"
class Queen : public Piece
{
public:
	Queen(Position position, Color color) : Piece(position, color) {
		type_ = Type::QUEEN;
	}
	string getName() const { return "Queen"; }
	Type getType() const override;
	vector<Position> getPossibleMoves(const Board& board) const;
	bool isValidMove(const Position& move, Board& board) const;
	~Queen() = default;
private:

};

