#include "engine.h"
#include "game.h"

using namespace std;

MenuScene menu;
StateScene stateScene;
DecisionScene decisionScene;

int main() {
	Engine::Start(1280, 720, "Steering", &menu);
	return 0;
}