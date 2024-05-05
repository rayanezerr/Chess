#include "Queen.hpp"
#include <cppitertools/range.hpp>
Piece::Type Queen::getType() const {
	return type_;
}
vector<Position> Queen::getPossibleMoves(const Board& board) const {
	vector<Position> possibleMoves;
	vector<Position> movements = { Position(1,0), Position(0,-1), Position(-1,0),
		Position(0,1), Position(1,1), Position(-1,1), Position(1,-1), Position(-1,-1)};

	for (auto&& moves : movements) {
		for (int i : iter::range(1, 8)) {
			Position newPos = position_ + (moves * i);
			if (!Position::isOutOfBounds(newPos))
				if (board.getPieceAt(newPos) == nullptr)
					possibleMoves.push_back(newPos);
				else if (board.getPieceAt(newPos)->getColor() != color_) {
					possibleMoves.push_back(newPos);
					break;
				}
				else
					break;
		}
	}
	return possibleMoves;
}
bool Queen::isValidMove(const Position& move, Board& board) const {
	vector<Position> possibleMoves = getPossibleMoves(board);
	auto it = find(possibleMoves.begin(), possibleMoves.end(), move);
	return (it != possibleMoves.end());
}

