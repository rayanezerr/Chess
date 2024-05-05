#pragma once
#include <vector>
#include <memory>
#include "Piece.hpp"
using namespace std;
class Board
{
public:
	Board();
	~Board();
	void addPiece(shared_ptr<Piece> piece);
	void removePiece(shared_ptr<Piece> piece);
	const shared_ptr<Piece>& getPieceAt(const Position& position) const;
	const shared_ptr<Piece> movePieceTo(const shared_ptr<Piece>& piece, const Position& position);
	void removePieceAt(const Position& position);
	void resetPieceTo(shared_ptr<Piece> piece, const Position& position);
	vector<shared_ptr<Piece>> getPieceByColor(Piece::Color color) const;
	void reset();
	Position getKingPosition(Piece::Color color) const;

private:
	vector<vector<shared_ptr<Piece>>> squares_;
};

