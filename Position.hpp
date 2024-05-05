#pragma once
#include <utility>
#include <iostream>
#include <QObject>

using namespace std;
class Position : public QObject
{
	Q_OBJECT
public:
	Position(int x, int y);
	Position(const Position& other) : QObject(other.parent()), x_(other.x_), y_(other.y_)  {}
	Position& operator=(const Position& other) {
		x_ = other.x_;
		y_ = other.y_;
		return *this;
	}

	pair<int, int> getPosition()  const;
	static bool isOutOfBounds(Position position);

	Position operator+(const Position& rhs) const;
	Position operator*(const int rhs) const;
	bool operator==(const Position& rhs) const;
	friend ostream& operator<<(ostream& os, const Position& position) {
		os << position.x_ << ", " << position.y_;
		return os;
	}
	~Position() = default;
	int x_;
	int y_;
	
public slots:
	void setPosition(int x, int y);

private:
};

