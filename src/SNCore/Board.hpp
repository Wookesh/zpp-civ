#ifndef BOARD_HPP
#define BOARD_HPP

#include <QVector>
#include "Resources.hpp"
#include <QPoint>

class Player;
class Tile;

class Board {
public:
	typedef QVector<const Tile *>::const_iterator const_iterator;
	const_iterator begin() const { return tiles_.constBegin(); };
	const_iterator end() const { return tiles_.constEnd(); };
	
	static const int MAXHEIGHT = 50;
	static const int MAXWIDTH = 50;
	Board(unsigned int width, unsigned int height, unsigned int seed = qrand());
	~Board();
	
	Tile *getTile(int x, int y) const;
	Tile *getTileAxial(int x, int y) const;
	Tile *getTileCube(int x, int y, int z) const;
	
	unsigned int nOfTilesWith(QVector<Tile *> &tiles, Resource resource) const;
	unsigned int getAbsoluteDistance(const Tile *tile1, const Tile *tile2) const;
	
	QVector<Tile *> getNeighbours(const Tile *tile) const;
	QVector<Tile *> getInRange(const Tile *tile, const int range) const;
	QVector<QVector<Tile *> > getReachable(Tile *tile, const int range, const Player *player) const;
	
	unsigned int width();
	unsigned int height();
	
	void updateBefore();
private:
	unsigned int height_;
	unsigned int width_;
	QVector<Tile *> tiles_;
};

#endif