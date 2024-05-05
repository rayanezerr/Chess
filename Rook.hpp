#pragma once
#include "Piece.hpp"
#include <vector>
#include "Board.hpp"
using namespace std;
class Rook : public Piece
{
public:
	Rook(Position position, Color color) : Piece(position, color) {
		type_ = Type::ROOK;
	}
	Type getType() const override;
	string getName() const { return "Rook"; }
	vector<Position> getPossibleMoves(const Board& board) const ;
	bool isValidMove(const Position& move, Board& board) const ;
	~Rook() = default;
private:
	
};

