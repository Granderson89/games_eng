#include "engine.h"
#include "game.h"

using namespace std;

MenuScene menu;
SteeringScene steeringScene;
//PathfindingScene pathfindingScene;

int main() {
  Engine::Start(1280, 720, "Steering",&menu);
  return 0;
}