#include "AttackAction.hpp"
#include "Soldier.hpp"

AttackAction::AttackAction(Soldier *mainObject, Unit *target) : 
	Action(mainObject, target->tile(), Type::Attack),
	target_(target)
{
	
}

bool AttackAction::perform()
{
	return dynamic_cast<Soldier *>(mainObject_)->attack(target_);
}
