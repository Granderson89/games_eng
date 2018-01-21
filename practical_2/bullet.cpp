#include "bullet.h"
#include "game.h"
using namespace sf;
using namespace std;

Bullet Bullet::bullets[256];
unsigned char Bullet::bulletPointer = 0;

Bullet::Bullet() {};

void Bullet::Update(const float &dt) {
	for (auto &b : bullets) {
		b._Update(dt);
	}
}

void Bullet::Render(sf::RenderWindow &window) {
	for (int i = 0; i < 256; i++) {
		window.draw(bullets[i]);
	}
}

void Bullet::Fire(const sf::Vector2f &pos, const bool mode) {
	bullets[++bulletPointer].setPosition(pos);
	bullets[bulletPointer]._mode = mode;
	bullets[bulletPointer].setTexture(spritesheet);
	if (mode == true)
		bullets[bulletPointer].setTextureRect(IntRect(32, 32, 32, 32));
	else
		bullets[bulletPointer].setTextureRect(IntRect(64, 32, 32, 32));

}

void Bullet::_Update(const float &dt) {
	if (getPosition().y < -32 || getPosition().y > gameHeight + 32)
	{
		// off screen - do nothing
		return;
	}
	else {
		move(0, dt * 200.0f * (_mode ? 1.0f : -1.0f));
		const FloatRect boundingBox = getGlobalBounds();

		for (auto s : ships) {
			if (!_mode && s == player) {
				// player bullets don't collide with player
				continue;
			}
			if (_mode && s != player) {
				// invader bullets don't collide with other invaders
				continue;
			}
			if (!s->is_exploded() &&
				s->getGlobalBounds().intersects(boundingBox)) {
				// Explode the ship
				s->Explode();
				// warp bullet off-screen
				setPosition(-100, -100);
				return;
			}
		}
	}
	
}