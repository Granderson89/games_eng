#include "pacman.h"
#include "ecm.h"
#include "system_renderer.h"
#include <LevelSystem.h>

using namespace sf;
using namespace std;

std::shared_ptr<Scene> gameScene;
std::shared_ptr<Scene> menuScene;
std::shared_ptr<Scene> activeScene;

#define GHOSTS_COUNT 4

const Keyboard::Key controls[4] = {
	Keyboard::Left,
	Keyboard::Right,
	Keyboard::Up,
	Keyboard::Down
};

/*
*	GAME SCENE
*/

void GameScene::load() {
	{
		auto pl = make_shared<Entity>();

		auto s = pl->addComponent<ShapeComponent>();
		s->setShape<sf::CircleShape>(12.f);
		s->getShape().setFillColor(Color::Yellow);
		s->getShape().setOrigin(Vector2f(12.f, 12.f));

		pl->addComponent<PlayerMovementComponent>();

		_ents.list.push_back(pl);
	}

	const sf::Color ghost_cols[]{ {208, 62, 25},	// red Blinky
								  {219, 133, 28},	// orange Clyde
								  {70, 191, 238},	// cyan Inky
								  {234, 130, 229} };//pink Pinky

	for (int i = 0; i < GHOSTS_COUNT; ++i) {
		auto ghost = make_shared<Entity>();
		auto s = ghost->addComponent<ShapeComponent>();
		s->setShape<sf::CircleShape>(12.f);
		s->getShape().setFillColor(ghost_cols[i % 4]);
		s->getShape().setOrigin(Vector2f(12.f, 12.f));

		ghost->addComponent<EnemyAIComponent>();

		_ents.list.push_back(ghost);
	}
}

void GameScene::update(double dt) {
	if (Keyboard::isKeyPressed(Keyboard::Tab)) {
		activeScene = menuScene;
	}
	Scene::update(dt);
}

void GameScene::respawn() {

}

void GameScene::render() {
	LevelSystem::render(Renderer::getWindow());
	Scene::render();
}

/*
*	MENU SCENE
*/

void MenuScene::load() {

}

void MenuScene::update(double dt) {
	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		activeScene = gameScene;
	}
	Scene::update(dt);
	text.setString("Almost Pacman");
}

void MenuScene::render() {
	Renderer::queue(&text);
	Scene::render();
}

/*
*	SHAPE COMPONENT
*/

void ShapeComponent::update(double dt) {
	_shape->setPosition(_parent->getPosition());
}

void ShapeComponent::render() { Renderer::queue(_shape.get()); }

sf::Shape& ShapeComponent::getShape() const { return *_shape; }

ShapeComponent::ShapeComponent(Entity* p) 
	: Component(p), _shape(make_shared<sf::CircleShape>()) {}

/*
*	ACTOR MOVEMENT COMPONENT
*/

void ActorMovementComponent::update(double dt) {}

ActorMovementComponent::ActorMovementComponent(Entity* p)
	: _speed(100.0f), Component(p) {}

//bool ActorMovementComponent::validMove(const sf::Vector2f& pos) {
//	return (LevelSystem::getTileAt(pos) != LevelSystem::WALL);
//}

void ActorMovementComponent::move(const sf::Vector2f& p) {
	auto pp = _parent->getPosition() + p;
	//if (validMove(pp)) {
		_parent->setPosition(pp);
	//}
}

void ActorMovementComponent::move(float x, float y) {
	move(Vector2f(x, y));
}

float ActorMovementComponent::getSpeed() const {
	return _speed;
}

void ActorMovementComponent::setSpeed(float speed) {
	_speed = speed;
}

/*
*	PLAYER MOVEMENT COMPONENT
*/

PlayerMovementComponent::PlayerMovementComponent(Entity* p)
	: ActorMovementComponent(p) {}

void PlayerMovementComponent::update(double dt) {
	// Move in four directions based on keys
	sf::Vector2f direction(0.0f, 0.0f);

	if (Keyboard::isKeyPressed(controls[0])) {
		direction.x = -1.0f;
	}
	if (Keyboard::isKeyPressed(controls[1])) {
		direction.x = 1.0f;
	}
	if (Keyboard::isKeyPressed(controls[2])) {
		direction.y = -1.0f;
	}
	if (Keyboard::isKeyPressed(controls[3])) {
		direction.y = 1.0f;
	}

	move(direction);
}

/*
*	EMENY AI COMPONENT
*/

EnemyAIComponent::EnemyAIComponent(Entity* p) 
	: ActorMovementComponent(p) {}

void EnemyAIComponent::update(double dt) {
	// Move randomly
	sf::Vector2f direction(0.0f, 0.0f);
	direction.x += (float)rand() / RAND_MAX * 2.0f - 1.0f;
	direction.y += (float)rand() / RAND_MAX * 2.0f - 1.0f;
	move(direction * _speed * (float)dt);
}