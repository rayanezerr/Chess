#include "Knight.hpp"
Piece::Type Knight::getType() const {
	return type_;
}
vector<Position> Knight::getPossibleMoves(const Board& board) const {
	vector<Position> possibleMoves;
	vector<Position> movements = { Position(2,1),Position(1,2),Position(-1,-2),
	Position(-2,1),Position(1,-2),Position(2,-1),Position(-1,2), Position(-2, -1)};
	for (auto&& moves : movements) {
		Position newPos = position_ + moves;
		if (!Position::isOutOfBounds(newPos))
			if (board.getPieceAt(newPos) == nullptr)
				possibleMoves.push_back(newPos);
			else if (board.getPieceAt(newPos)->getColor() != color_) {
				possibleMoves.push_back(newPos);
			}
	}
	return possibleMoves;
}
bool Knight::isValidMove(const Position& move, Board& board) const {
	vector<Position> possibleMoves = getPossibleMoves(board);
	auto it = find(possibleMoves.begin(), possibleMoves.end(), move);
	return (it != possibleMoves.end());
}
