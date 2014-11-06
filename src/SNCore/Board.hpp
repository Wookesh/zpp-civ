#ifndef BOARD_HPP
#define BOARD_HPP

#include <QVector>
#include "Tile.hpp"

class Board {
public:
	Board(unsigned int width, unsigned int height);
	~Board();
	
	Tile *getTile(int x, int y) const;
	Tile *getTileAxial(int x, int y) const;
	Tile *getTileCube(int x, int y, int z) const;
	
	unsigned int getAbsoluteDistance(const Tile *tile1, const Tile *tile2) const;
	
	QVector<Tile *> getNeighbours(const Tile *tile) const;
	QVector<Tile *> getInRange(const Tile *tile, const int range) const;
private:
	unsigned int height_;
	unsigned int width_;
	QVector<Tile *> tiles_;
};

#endif