#include "ship.h"
#include "game.h"
#include "bullet.h"
using namespace sf;
using namespace std;

bool Invader::direction = true;
float Invader::speed = 20.0f;
const float playerSpeed = 400.f;

const Keyboard::Key controls[3] = {
	Keyboard::Left,  // Player1 LEFT
	Keyboard::Right, // Player1 RIGHT
	Keyboard::Space
};

Ship::Ship() {};

Ship::Ship(IntRect ir) : Sprite() {
	_sprite = ir;
	setTexture(spritesheet);
	setTextureRect(_sprite);
	_exploded = false;
};

void Ship::Update(const float &dt) {
	if (is_exploded()) {
		explosionTimer -= dt;
		if (explosionTimer <= -2) {
			setTextureRect(IntRect(-32, -32, 32, 32));
		}
	}
}

void Ship::Explode() {
	setTextureRect(IntRect(128, 32, 32, 32));
	_exploded = true;
}

bool Ship::is_exploded() const{
	return _exploded;
}

// Define the ship deconstructor
// Although we set this to pure virtual, we still have to define it
Ship::~Ship() = default;

Invader::Invader() : Ship() {}

Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) {
	setOrigin(16, 16);
	setPosition(pos);
}

void Invader::Update(const float &dt) {
	Ship::Update(dt);

	move(dt * (direction ? 1.0f : -1.0f) * speed, 0);

	if ((direction && getPosition().x > gameWidth - 16) ||
		(!direction && getPosition().x < 16)) {
		direction = !direction;
		for (int i = 0; i < ships.size() - 1; ++i) {
			ships[i]->move(0, 24);
		}
	}

	static float firetime = 0.0f;
	firetime -= dt;

	if (firetime <= 0 && rand() % 100 == 0) {
		Bullet::Fire(getPosition(), true);
		firetime = 4.0f + (rand() % 60);
	}
}

Player::Player() : Ship(IntRect(160, 32, 32, 32)) {
	setPosition({ gameHeight * .5f, gameHeight - 32.f });
}

void Player::Update(const float &dt) {
	Ship::Update(dt);;
	float direction = 0.0f;
	if (Keyboard::isKeyPressed(controls[0])) {
		direction--;
	}
	if (Keyboard::isKeyPressed(controls[1])) {
		direction++;
	}
	move(direction * playerSpeed * dt, 0);
	if (getPosition().x < 0) {
		move(2, 0);
	}
	else if (getPosition().x + 32 > gameWidth) {
		move(-2, 0);
	}
	
	static float firetime = 0.0f;
	firetime -= dt;
	if (firetime <= 0 && Keyboard::isKeyPressed(controls[2])) {
		Bullet::Fire(getPosition(), false);
		firetime = 0.7f;
	}
}