#pragma once
#include "Piece.hpp"
#include <vector>
#include "Board.hpp"
using namespace std;
class Knight : public Piece
{
public:
	Knight(Position position, Color color) : Piece(position, color) {
		type_ = Type::KNIGHT;
	}
	Type getType() const override;
	string getName() const { return "Knight"; }
	vector<Position> getPossibleMoves(const Board& board) const;
	bool isValidMove(const Position& move, Board& board) const;
	~Knight() = default;
private:

};