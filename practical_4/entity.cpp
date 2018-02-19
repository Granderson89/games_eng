#include "entity.h"

using namespace std;
using namespace sf;

void EntityManager::update(double dt) {
	for each (shared_ptr<Entity> e in list) {
		e->update(dt);
	}
}

void EntityManager::render() {
	for each (shared_ptr<Entity> e in list) {
		e->render();
	}
}