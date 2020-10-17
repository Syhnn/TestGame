#include "GameCommands.hpp"

#include <iostream>
#include "Yume/Engine.hpp"

#include "Player.hpp"


using namespace std;


// Init

Engine* GameCommands::engine = nullptr;
Player* GameCommands::player = nullptr;

void GameCommands::init(Engine* e, Player* p) {
  if (!e) {
    cout << "Link to Engine is needed!" << endl;
  } else {
    engine = e;
  }

  if (!p) {
    cout << "Link to Player is needed!" << endl;
  } else {
    player = p;
  }
}


// Commands

void GameCommands::moveRight() {
  player->vx += 1;
}

void GameCommands::stopMoveRight() {
  player->vx -= 1;
}

void GameCommands::moveLeft() {
  player->vx -= 1;
}

void GameCommands::stopMoveLeft() {
  player->vx += 1;
}

void GameCommands::moveUp() {
  player->vy -= 1;
}

void GameCommands::stopMoveUp() {
  player->vy += 1;
}

void GameCommands::moveDown() {
  player->vy += 1;
}

void GameCommands::stopMoveDown() {
  player->vy -= 1;
}

void GameCommands::exitToMenu() {
  engine->popState();
}
