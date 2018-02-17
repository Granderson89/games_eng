#pragma once
#include "scene.h"
#include "ecm.h"
#include <memory>

extern std::shared_ptr<Scene> gameScene;
extern std::shared_ptr<Scene> menuScene;
extern std::shared_ptr<Scene> activeScene;


class MenuScene : public Scene {
private:
	sf::Text text;

public:
	MenuScene() = default;
	void update(double dt) override;
	void render() override;
	void load() override;
};

class GameScene : public Scene {
private:
	sf::Text text;
	sf::Clock scoreClock;

	void respawn();

public:
	GameScene() = default;
	void update(double dt) override;
	void render() override;
	void load() override;
};

class ShapeComponent : public Component {
protected:
	std::shared_ptr<sf::Shape> _shape;
public:
	ShapeComponent() = delete;
	explicit ShapeComponent(Entity *p);

	void update(double dt) override;
	void render() override;

	sf::Shape &getShape() const;

	template <typename T, typename... Targs>
	void setShape(Targs... params) {
		_shape.reset(new T(params...));
	}
};

class ActorMovementComponent : public Component {
protected:
	//bool validMove(const sf::Vector2f&);
	float _speed;

public:
	explicit ActorMovementComponent(Entity* p);
	ActorMovementComponent() = delete;

	float getSpeed() const;
	void setSpeed(float _speed);

	void move(const sf::Vector2f&);
	void move(float x, float y);

	void render() override {}
	void update(double dt) override;
};

class PlayerMovementComponent : public ActorMovementComponent {
public:
	PlayerMovementComponent() = delete;
	explicit PlayerMovementComponent(Entity* parent);

	void update(double dt) override;
};

class EnemyAIComponent : public ActorMovementComponent {
public:
	EnemyAIComponent() = delete;
	explicit EnemyAIComponent(Entity* parent);

	void update(double dt) override;
};