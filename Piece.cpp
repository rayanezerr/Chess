#include "Piece.hpp"
Piece::Piece(Position position, Color color) 
	: position_(position), color_(color) {}

Position Piece::getPosition() const {
	return position_;
}

Piece::Color Piece::getColor() const {
	return color_;
}

Piece::Type Piece::getType() const {
	return type_;
}

string Piece::getName() const {
	return "None";
}

void Piece::resetTo(const Position& position) {
	position_.x_ = position.x_;
	position_.y_ = position.y_;
}

void Piece::setPosition(Position position) {
	position_ = position;
}

Piece::Color Piece::getOppositeColor() const {
	if (color_ == Color::WHITE)
		return Color::BLACK;
	return Color::WHITE;
}

