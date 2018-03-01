#include "pacman.h"
#include "ecm.h"
#include "system_renderer.h"
#include "actor_movement_component.h"
#include "shape_component.h"
#include "pickup_component.h"
#include <LevelSystem.h>

using namespace sf;
using namespace std;

std::shared_ptr<Scene> gameScene;
std::shared_ptr<Scene> menuScene;
std::shared_ptr<Scene> activeScene;

#define GHOSTS_COUNT 4

vector<shared_ptr<Entity>> ghosts;
shared_ptr<Entity> player;
vector<shared_ptr<Entity>> nibbles;
vector<shared_ptr<Entity>> npcs;


Font font;

/*
*	GAME SCENE
*/

std::shared_ptr<Entity> GameScene::makeNibble(sf::Vector2f& nl, bool big) {
	auto cherry = make_shared<Entity>();
	auto s = cherry->addComponent<ShapeComponent>();

	// set colour
	if (big == true) {
		s->setShape<sf::CircleShape>(10.f);
		s->getShape().setFillColor(Color::Blue);
		s->getShape().setOrigin(10.f, 10.f);
	}
	else {
		s->setShape<sf::CircleShape>(6.f);
		s->getShape().setFillColor(Color::White);
		s->getShape().setOrigin(6.f, 6.f);
	}
	auto ps = cherry->addComponent<PickupComponent>();
	cherry->setPosition(nl + Vector2f(10.f, 10.f));

	ps->setEntities(npcs);

	return cherry;
}

void GameScene::respawn() {
	_ents.list[0]->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));

	auto ghost_spawns = ls::findTiles(ls::ENEMY);
	for (int i = 1; i < _ents.list.size(); ++i) {
		_ents.list[i]->setPosition(
			ls::getTilePosition(ghost_spawns[rand() % ghost_spawns.size()]));
	}

	// clear any remaining nibbles
	for (auto n : nibbles) {
		n->setForDelete();
		n.reset();
	}
	nibbles.clear();

	// white nibbles
	auto nibbleLoc = LevelSystem::findTiles(LevelSystem::EMPTY);
	for (const auto& nl : nibbleLoc) {
		auto loc = static_cast<Vector2f>(LevelSystem::getTilePosition(nl));
		auto cherry = makeNibble(loc, false);
		// add to _ents and nibbles list
		_ents.list.push_back(cherry);
		nibbles.push_back(cherry);
	}
	// blue nibbles
	nibbleLoc = LevelSystem::findTiles(LevelSystem::WAYPOINT);
	for (const auto& nl : nibbleLoc) {
		auto loc = static_cast<Vector2f>(LevelSystem::getTilePosition(nl));
		auto cherry = makeNibble(loc, true);
		// add to _ents and nibbles list
		_ents.list.push_back(cherry);
		nibbles.push_back(cherry);
	}
}

void GameScene::load() {
	ls::loadLevelFile("res/pacman.txt", 25.0f);

	{
		auto pl = make_shared<Entity>();

		auto s = pl->addComponent<ShapeComponent>();
		s->setShape<sf::CircleShape>(12.f);
		s->getShape().setFillColor(Color::Yellow);
		s->getShape().setOrigin(Vector2f(12.f, 12.f));

		pl->addComponent<PlayerMovementComponent>();

		_ents.list.push_back(pl);
		npcs.push_back(pl);
		player = pl;
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

		ghosts.push_back(ghost);
		npcs.push_back(ghost);
		_ents.list.push_back(ghost);
	}

	respawn();
}

void GameScene::update(double dt) {
	if (Keyboard::isKeyPressed(Keyboard::Tab)) {
		activeScene = menuScene;
	}
	Scene::update(dt);

	for (auto& g : ghosts) {
		if (length(g->getPosition() - player->getPosition()) < 30.0f) {
			respawn();
		}
	}
}

void GameScene::render() {
	ls::render(Renderer::getWindow());
	Scene::render();
}

/*
*	MENU SCENE
*/

void MenuScene::load() {
	font.loadFromFile("res/fonts/RobotoMono-Regular.ttf");
	text.setFont(font);
	text.setCharacterSize(32);
	text.setPosition(800 * .5f, 600 * .5f);
	text.setColor(Color::White);
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