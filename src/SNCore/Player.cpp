#include "Player.hpp"
#include "Objects/Prototypes/Prototypes.hpp"
#include "Objects/Town.hpp"
#include "Objects/Unit.hpp"
#include "Tile.hpp"
#include "Config.hpp"

#include <QtCore>

const QHash<Resource, SNTypes::amount> Player::BASE_BUILDING_COST = {
	{Resource::Gold, SNCfg::BUILDING_GOLD_COST},
	{Resource::Research, SNCfg::BUILDING_RESEARCH_COST},
	{Resource::Food, SNCfg::BUILDING_FOOD_COST}
};

Player::Player(const QString &name, Qt::GlobalColor color) : capital_(nullptr), name_(name), color_(color)
{
	prototypes_[PrototypeType::Infantry] = new SoldierPrototype(PrototypeType::Infantry);
	prototypes_[PrototypeType::Heavy] = new SoldierPrototype(PrototypeType::Heavy);
	prototypes_[PrototypeType::Artillery] = new SoldierPrototype(PrototypeType::Artillery);
	soldierPrototypes_ = prototypes_;
	prototypes_[PrototypeType::Settler] = new SettlerPrototype();
	
	for (Resource r : Resource::labels())
		resources_[r] = 0;
	
	bonuses_ = {
		{BonusType::War, {{1, false}, {2, false}, {3, false}}},
		{BonusType::Def, {{1, false}, {2, false}, {3, false}}},
		{BonusType::Eco, {{1, false}, {2, false}, {3, false}}}
	};
	
	buildingCost_ = BASE_BUILDING_COST;
}

Player::~Player()
{
	for (auto element : prototypes_.keys()) {
		Prototype *aux = prototypes_.take(element);
		delete aux;
	}
	
	while (!units_.isEmpty()) {
		Unit *aux = units_.takeLast();
		delete aux;
	}
	
	while (!towns_.isEmpty()) {
		Town *aux = towns_.takeLast();
		delete aux;
	}
}

QString Player::name() const
{
	return name_;
}

void Player::obtainTown(Town *town)
{
	towns_.push_back(town);
}

void Player::destroyTown (Town *town) {
	for (auto iter = towns_.begin(); iter != towns_.end(); ++iter) {
		if (*(iter) == town) {
			towns_.erase(iter);
			break;
		}
	}
}

Qt::GlobalColor Player::color() const
{
	return color_;
}

unsigned int Player::getTownCount() {
	return towns_.count();
}

unsigned int Player::resource(Resource resource) const
{
	return resources_[resource];
}

void Player::addResource(Resource resource, unsigned int val)
{
	qDebug() << "Player" << name() << "received" << val << "of" << QString(resource);
	resources_[resource] += val;
}

bool Player::removeResource(Resource resource, unsigned int val)
{
	if (resources_[resource] >= val) {
		resources_[resource] -= val;
		return true;
	}
	return false;
}

void Player::updateBefore() {
	// internal stuff
	// doSth()...
	
	// Units
	for (auto unit : units_) {
		unit->updateBefore();
	}
	
	// Towns
	for (auto town : towns_) {
		town->updateBefore();
	}
	
	// internal stuff
	// wrapUp()...
}

void Player::updateAfter()
{
	// internal stuff
	// doSth()...
	
	// Units
	for (auto unit : units_) {
		unit->updateAfter();
	}
	
	// Towns
	for (auto town : towns_) {
		town->updateAfter();
	}
	
	// internal stuff
	// wrapUp()...
}

Town *Player::capital() 
{
	return capital_;
}

void Player::setCapital (Town *town) 
{
	capital_ = town;
}

Unit *Player::createUnit(PrototypeType type, Tile *tile) 
{
	Unit *newUnit = prototypes_[type]->createUnit(tile, this);
	units_.push_back(newUnit);
	tile->setUnit(newUnit);
	
	return newUnit;
}

void Player::destroyUnit(Unit *toKill) 
{
	for (auto iter = units_.begin(); iter != units_.end(); ++iter) {
		if (*(iter) == toKill) {
			units_.erase(iter);
			break;
		}
	}
}

Prototype *Player::prototype(PrototypeType type)
{
	return prototypes_[type];
}

QList< Prototype * > Player::prototypes() 
{
	return prototypes_.values();
}

QList< Prototype * > Player::soldierPrototypes() 
{
	return soldierPrototypes_.values();
}

bool Player::applyBonus(BonusType type, SNTypes::tier tier) 
{
	Bonus *bonus = BonusManager::get()->getBonus(type, tier);
	if (bonus->apply(this)) {
		bonuses_[bonus->type()][bonus->tier()] = true;
		removeResource(Resource::Research, bonus->cost());
		return true;
	} else
		return false;
}

bool Player::hasBonus(BonusType type, SNTypes::tier tier) const
{
	return bonuses_[type][tier];
}

bool Player::canAffordBuilding(Resource type) {
	return buildingCost_[type] <= resources_[Resource::Gold];
		
}

void Player::payForBuilding(Resource type) {
	resources_[Resource::Gold] -= buildingCost_[type];
}