#include "scene_state.h"
#include "../enemy_states.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_basic_movement.h"
#include "../components/cmp_state_machine.h"
#include "../steering_states.h"
#include <LevelSystem.h>

using namespace std;
using namespace std::chrono;
using namespace sf;

void StateScene::Load() {
	auto player = makeEntity();
	player->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, Engine::GetWindow().getSize().y / 2));
	auto s = player->addComponent<ShapeComponent>();
	s->setShape<CircleShape>(10.0f);
	s->getShape().setFillColor(Color::Red);
	player->addComponent<BasicMovementComponent>();

	auto enemy = makeEntity();
	enemy->setPosition(Vector2f(50.0f, 50.0f));
	s = enemy->addComponent<ShapeComponent>();
	s->setShape<CircleShape>(10.0f);
	s->getShape().setFillColor(Color::Blue);

	auto sm = enemy->addComponent<StateMachineComponent>();
	sm->addState("seek", make_shared<SeekState>(enemy, player));
	sm->addState("flee", make_shared<FleeState>(enemy, player));
	sm->changeState("seek");
}

void StateScene::UnLoad() {
	Scene::UnLoad();
}

void StateScene::Update(const double &dt) {
	Scene::Update(dt);
}

void StateScene::Render() {
	Scene::Render();
}