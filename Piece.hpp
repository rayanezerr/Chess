#pragma once
#include "Position.hpp"
#include <QObject>
class Board;
class Piece : public QObject
{
	Q_OBJECT
public:
	enum class Color { WHITE, BLACK };
	enum class Type { PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING };

	Piece(Position position, Color color);
	Position getPosition() const;
	void setPosition(Position position);
	Color getColor() const;
	virtual Type getType() const = 0;
	virtual string getName() const = 0;
	virtual vector<Position> getPossibleMoves(const Board& board) const = 0;
	virtual bool isValidMove(const Position& move, Board& board) const = 0;
	Color getOppositeColor() const;
	void resetTo(const Position& position);
	virtual ~Piece() = default;
	
protected:
	Position position_ = Position(0,0);
	Color color_;
	Type type_;
};
