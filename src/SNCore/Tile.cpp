#include "Tile.hpp"
#include "Town.hpp"
#include "Unit.hpp"

Tile::Tile(unsigned int x_, unsigned int y_): position_(x_, y_) {

}

Tile::~Tile() {

}

QList<const Object *> Tile::getObjects() const {
	QList<const Object *> l;

	if (town_ != nullptr) {
		l.push_back (town_);
	}

	if (unit_ != nullptr) {
		l.push_back (unit_);
	}

	return l;
}

QPoint Tile::position() const {
	return position_;
}

QPoint Tile::axial() const {
	const int q = position_.x();
	const int r = position_.y();
	
	const int x = q;
	const int y = r - (q - (q&1)) / 2;

	QPoint positionAxial(x, y);
	return positionAxial;
}

void Tile::setTown(Town *town) {
	town_ = town;
}

void Tile::setUnit(Unit *unit) {
	unit_ = unit;
}