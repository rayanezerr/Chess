#include "Position.hpp"
#include <QDebug>
Position::Position(int x, int y) : x_(x), y_(y) {};

pair<int, int> Position::getPosition() const {
	return make_pair(x_, y_);
}

void Position::setPosition(int x, int y) {
	x_ = x;
	y_ = y;
}

Position Position::operator+(const Position& rhs) const {
	return Position(x_ + rhs.x_, y_ + rhs.y_);
}

Position Position::operator*(const int rhs) const {
	return Position(x_ * rhs, y_ * rhs);
}

bool Position::operator==(const Position& rhs) const {
	return x_ == rhs.x_ && y_ == rhs.y_;
}

bool Position::isOutOfBounds(Position position) {
	return position.x_ < 0 || position.x_ > 7 || position.y_ < 0 || position.y_ > 7;
}
