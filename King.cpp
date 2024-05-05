#include "King.hpp"
#include "qdebug.h"

Piece::Type King::getType() const {
	return type_;
}
vector<Position> King::getPossibleMoves(const Board& board) const {
	vector<Position> possibleMoves;
	vector<Position> movements = { Position(1,0),Position(0,-1),Position(-1,0),Position(0,1),
		Position(1,1),Position(-1,1),Position(1,-1),Position(-1,-1)
	};
	for (auto&& moves : movements) {
		Position newPos = position_ + moves;
		if (!Position::isOutOfBounds(newPos)) {
			if (board.getPieceAt(newPos) == nullptr)
				possibleMoves.push_back(newPos);
			else if (board.getPieceAt(newPos)->getColor() != color_) {
				possibleMoves.push_back(newPos);
				continue;
			}
			else
				continue;
		}
	}
	return possibleMoves;
}
bool King::isValidMove(const Position& move, Board& board) const {
	vector<Position> possibleMoves = getPossibleMoves(board);
	auto it = find(possibleMoves.begin(), possibleMoves.end(), move);
	if (it == possibleMoves.end())
		return false;
	shared_ptr<Piece> king = board.getPieceAt(position_);
	board.removePiece(king);
	vector<shared_ptr<Piece>> oppositePieces = board.getPieceByColor(this->getOppositeColor());
	bool returnValue = true;
	for (auto&& piece : oppositePieces) {
		vector<Position> possibleMovesOpps = piece->getPossibleMoves(board);
		auto it = find(possibleMovesOpps.begin(), possibleMovesOpps.end(), move);
		if (it != possibleMovesOpps.end()) {
			returnValue = false;
			break;
		}
	}
	board.addPiece(king);
	return returnValue;
	
}




bool King::isInCheck(const Board& board) const {
	vector<shared_ptr<Piece>> oppositePieces = board.getPieceByColor(this->getOppositeColor());
	for (auto&& piece : oppositePieces) {
		vector<Position> possibleMoves = piece->getPossibleMoves(board);
		auto it = find(possibleMoves.begin(), possibleMoves.end(), position_);
		if (it != possibleMoves.end())
			return true;
	}
	return false;
}




