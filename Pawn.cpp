#include "Pawn.hpp"
#include <cppitertools/range.hpp>
Piece::Type Pawn::getType() const {
	return type_;
}
vector<Position> Pawn::getPossibleMoves(const Board& board) const {
	vector<Position> possibleMoves;
	vector<Position> movements;
	if (color_ == Color::WHITE)
		movements = { Position(1,0), Position(1,1), Position(1,-1)};
	else
		movements = { Position(-1,0), Position(-1, 1), Position(-1, -1)};
	for (auto&& move : movements) {
		Position newPos = position_ + move;
		if (!Position::isOutOfBounds(newPos)) {
			if (move.getPosition().second == 0) {
				if (board.getPieceAt(newPos) == nullptr) {
					possibleMoves.push_back(newPos);
					if ((position_.x_ == 1 && color_ == Color::WHITE) || (position_.x_ == 6 && color_ == Color::BLACK)) {
						Position newPos2 = newPos + move;
						if (board.getPieceAt(newPos2) == nullptr)
							possibleMoves.push_back(newPos2);
					}
				}
			}
			else if (board.getPieceAt(newPos) != nullptr && board.getPieceAt(newPos)->getColor() != color_)
				possibleMoves.push_back(newPos);
		}
	}
	return possibleMoves;
}
bool Pawn::isValidMove(const Position& move, Board& board) const {
	vector<Position> possibleMoves = getPossibleMoves(board);
	auto it = find(possibleMoves.begin(), possibleMoves.end(), move);
	return (it != possibleMoves.end());
}

