#pragma once
#include "Piece.hpp"
#include <vector>
#include "Board.hpp"
using namespace std;
class Pawn : public Piece
{
public:
	Pawn(Position position, Color color) : Piece(position, color) {
		type_ = Type::PAWN;
	}
	Type getType() const override;
	string getName() const { return "Pawn"; }
	vector<Position> getPossibleMoves(const Board& board) const ;
	bool isValidMove(const Position& move, Board& board) const ;
	~Pawn() = default;
private:
	
};
