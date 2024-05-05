#include "Board.hpp"
#include <QDebug>
Board::Board() {
	squares_.resize(8);
	for (int i = 0; i < 8; i++) {
		squares_[i].resize(8);
		for (int j = 0; j < 8; j++) {
			squares_[j].push_back(nullptr);
		}
	}

}

Board::~Board() = default;

void Board::addPiece(shared_ptr<Piece> piece) {
	squares_[piece->getPosition().x_][piece->getPosition().y_] = piece;
}

void Board::removePiece(shared_ptr<Piece> piece) {
	squares_[piece->getPosition().x_][piece->getPosition().y_] = nullptr;
}

void Board::reset() {
	for (auto&& line : squares_)
		for (auto&& piece : line)
			if (piece != nullptr)
				removePiece(piece);
}

const shared_ptr<Piece>& Board::getPieceAt(const Position& position) const {
	return squares_[position.x_][position.y_];
}

const shared_ptr<Piece> Board::movePieceTo(const shared_ptr<Piece>& piece, const Position& position) {
	squares_[piece->getPosition().x_][piece->getPosition().y_] = nullptr;
	shared_ptr<Piece> oldPiece = squares_[position.x_][position.y_];
	piece->setPosition(position);
	squares_[position.x_][position.y_] = piece;
	return oldPiece;
}

void Board::resetPieceTo(shared_ptr<Piece> piece, const Position& position) {
	squares_[piece->getPosition().x_][piece->getPosition().y_] = nullptr;
	piece->resetTo(position);
	squares_[position.x_][position.y_] = piece;
}

vector<shared_ptr<Piece>> Board::getPieceByColor(Piece::Color color) const {
	vector<shared_ptr<Piece>> pieces;
	for (auto&& line : squares_)
		copy_if(line.begin(), line.end(), back_inserter(pieces), [&](shared_ptr<Piece> piece) {return piece != nullptr &&piece->getColor() == color; });
	return pieces;
}

void Board::removePieceAt(const Position& position) {
	squares_[position.x_][position.y_] = nullptr;
}

Position Board::getKingPosition(Piece::Color color) const {
	for (auto&& line : squares_) {
		for (auto&& piece : line) {
			if (piece != nullptr && piece->getType() == Piece::Type::KING && piece->getColor() == color) {
				return piece->getPosition();
			}
		}
	}
	return Position(-1, -1);
}
