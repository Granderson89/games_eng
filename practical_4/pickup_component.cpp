#include "pickup_component.h"
#include "actor_movement_component.h"

/*
*	PICKUP COMPONENT
*/
PickupComponent::PickupComponent(Entity* p)
	: Component(p) {}

void PickupComponent::update(double dt) {
	for (auto e : _ents) {
		if (length(_parent->getPosition() - e->getPosition()) < 30.0f) {

			auto cp = e->GetComponent<ActorMovementComponent>();

			if (cp != nullptr) {
				cp->setSpeed(cp->getSpeed() + 1.0f);
				_parent->setForDelete();
				break;
			}
		}
	}
}

void PickupComponent::setEntities(std::vector <std::shared_ptr<Entity>>& e) {
	_ents = e;
}