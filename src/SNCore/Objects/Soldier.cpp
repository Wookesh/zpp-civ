#include "Soldier.hpp"
#include "../Tile.hpp"
#include "Town.hpp"
#include "../GameManager.hpp"

Soldier::Soldier(Tile* tile, const Prototype* prototype, Player *owner, QObject* parent): Unit(tile, prototype, owner, parent)
{

}

bool Soldier::canAttack(Tile* currTile)
{
	if((GameManager::get()->currentPlayer() == owner()) &&
		(currTile->unit() != nullptr) &&
		(currTile->unit()->owner() != owner()))
		return true;
	
	return false;
}
bool Soldier::attack(Unit* unit)
{
	if(canAttack(unit->tile())) {
		unit->getAttacked(this);
		return true;
	} else {
		return false;
	}
}

bool Soldier::canCapture(Tile* currTile)
{	
	if((GameManager::get()->currentPlayer() == owner()) &&
		(currTile->town() != nullptr) &&
		(currTile->town()->owner() != owner()))
		return true;
	
	return false;
}
bool Soldier::capture(Town* town)
{
	if(canCapture(town->tile())) {
		town->setOwner(owner());
		return true;
	} else {
		return false;
	}
}

void Soldier::getAttacked(Unit *)
{

}

