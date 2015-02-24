#include "Town.hpp"
#include "Unit.hpp"
#include "../Tile.hpp"
#include "../Player.hpp"
#include "../GameManager.hpp"
#include <Board.hpp>
#include <QDebug>
#include <QtAlgorithms>

Town::Town(Tile *tile, Player *owner, const QString &name, QObject *parent) :
	Object(tile, ObjectType::Town, owner, parent), name_(name), population_(1),  food_(0)
{
	owner->obtainTown(this);
	for (Tile *nTile : GameManager::get()->board()->getInRange(tile_, 1))
		if (nTile->localTown() == nullptr) {
			nTile->setLocalTown(this);
			townTiles_.push_back(nTile);
		}
	tile->setTown(this);
	setFoodGoal();
}

Town::~Town()
{
	if (tile_ != nullptr)
		tile_->setTown(nullptr);
	
	for (Tile *tile : townTiles_)
		tile->setLocalTown(nullptr);
	
	if (owner_ != nullptr)
		owner_->destroyTown(this);
}

void Town::setFoodGoal() {
	// Equation borrowed from Civ5 (almost, it's a bit different)
	foodGoal_ = qFloor(15 + 6 * (population_ - 1) + (population_ - 1) * (population_ - 1));
}

void Town::addNewTile() {
	Board *board = GameManager::get()->board();
	Tile *newTile = chooseBestTile(board->getSurroundings(this));
	if (newTile == nullptr)
		return;
	
	townTiles_.push_back(newTile);
	newTile->setLocalTown(this);
}

/*
 * Function for comparing tiles while deciding which one to adjacent to a town.
 * Prefers tiles with higher resource production and closer to the town;
 */
bool compareTiles(Tile* &tile1, Tile* &tile2) {
	int weight1 = tile1->resourceProduction();
	int weight2 = tile2->resourceProduction();
	QVector<Tile *> neigh1 = GameManager::get()->board()->getNeighbours(tile1);
	int ctr = 1;
	for (Tile *tile : neigh1) {
		if (tile->town() == tile1->town()) {
			++ctr;
			weight1 += ctr;
		}
	}
	ctr = 0;
	QVector<Tile *> neigh2 = GameManager::get()->board()->getNeighbours(tile1);
	for (Tile *tile : neigh2) {
		if (tile->town() == tile2->town()) {
			++ctr;
			weight2 += ctr;
		}
	}

	return weight1 < weight2;
}

Tile *Town::chooseBestTile(QVector< Tile * > tiles) {
	if (tiles.empty())
		return nullptr;
	
	qSort(tiles.begin(), tiles.end(), compareTiles);
	
	// Cause the best element will be at the end
	return tiles.back();
}


void Town::updateBefore() 
{
	qDebug() << name() << __FUNCTION__;
	for (Tile *tile : townTiles_)
		if (tile->resource() != Resource::None) {
			tile->gatherResource(this);
		}
		
	if (food_ > foodGoal_) {
		food_ = food_ - foodGoal_;
		++population_;
		setFoodGoal();
		addNewTile();
	}
}


QString Town::name() const
{
	return name_;
}

void Town::updateAfter()
{
	
}

void Town::addFood(SNTypes::amount food) {
	food_ += food;
}


Unit *Town::createUnit(PrototypeType type)
{
	if (!canRecruit(type))
		return nullptr;
	
	owner_->removeResource(Resource::Gold, owner_->prototype(type)->cost());
	Unit *newUnit = owner_->createUnit(type, tile_);
	return newUnit;
}

void Town::getCaptured(Player *player)
{
	setOwner(player);
	player->obtainTown(this);
}

bool Town::canRecruit(PrototypeType type)
{
	if (tile_->unit() == nullptr &&
		GameManager::get()->currentPlayer() == owner() &&
		owner()->resource(Resource::Gold) >= owner()->prototype(type)->cost())
		return true;
	return false;
}
