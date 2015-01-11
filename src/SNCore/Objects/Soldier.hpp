#ifndef SOLDIER_HPP
#define SOLDIER_HPP
#include "Unit.hpp"

class SoldierPrototype;
class Tile;
class Town;

class Soldier : public Unit {
Q_OBJECT
public:
	Soldier(Tile *tile, const SoldierPrototype *prototype, Player *owner, QObject *parent = nullptr);
	
	bool canCapture(Tile *currTile);
	bool capture(Town *town);
	
	bool canAttack(Tile *currTile);
	bool attack(Unit *unit);
	
	float attackBonus(Soldier *soldier);
	
	SNTypes::ap attackCost() const;
	SNTypes::distance attackRange() const;
	SNTypes::dmg damage() const;
	
	virtual void getAttacked(Soldier *) override;
};


#endif
