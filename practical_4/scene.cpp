#include "scene.h"

using namespace std;

void Scene::update(double dt) {
	_ents.update(dt);
}

void Scene::render() {
	_ents.render();
}

vector<shared_ptr<Entity>>& Scene::getEnts() {
	return _ents.list;
}