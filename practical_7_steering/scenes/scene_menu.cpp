#include "scene_menu.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace std;
using namespace sf;

void MenuScene::Load() {
  cout << "Menu Load \n";
  {
    auto txt = makeEntity();
    auto t = txt->addComponent<TextComponent>(
        "Movement Demos\nPress 1 for Steering\nPress 2 for Pathfinding");
  }
  setLoaded(true);
}

void MenuScene::Update(const double& dt) {
	if (sf::Keyboard::isKeyPressed(Keyboard::Num1)) {
		Engine::ChangeScene(&steeringScene);
	}
	else if (sf::Keyboard::isKeyPressed(Keyboard::Num2)) {
		Engine::ChangeScene(&pathfindingScene);
	}
  Scene::Update(dt);
}
