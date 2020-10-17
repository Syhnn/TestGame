#include "Game.hpp"

#include <iostream>
#include <string>
#include "Yume/DisplayManager.hpp"
#include "Yume/KeyBinds.hpp"

#include "GameCommands.hpp"


using namespace std;


// Constructors and destructor

Game::Game() :
  GameState(),

  text(-1)
{}


// Public methods

void Game::init(Engine* e, DisplayManager* dm) {
  // import assets
  string path = "assets/testchar.png";
  int tmp = dm->loadTexture(path, 32, 32);
  if (tmp == -1) {
    cout << "Couldn't load texture " << path << endl;
  } else {
    for (int pose(0); pose < 4; ++pose) {
      for (int frame(0); frame < 4; ++frame) {
        dm->addTextureClip(tmp, frame * 32, pose * 32, 32, 32);
      }
    }
  }

  text = dm->loadText("abcdefghijklmnopqrstuvwxyz");
  if (text == -1) {
    cout << "Couldn't load text" << endl;
  }

  // create entities
  player.texture_id = tmp;
  addEntity(&player);

  GameCommands::init(e, &player);
  kb->bindKeyDown(Key::D, GameCommands::moveRight);
  kb->bindKeyDown(Key::Q, GameCommands::moveLeft);
  kb->bindKeyDown(Key::Z, GameCommands::moveUp);
  kb->bindKeyDown(Key::S, GameCommands::moveDown);
  kb->bindKeyUp(Key::D, GameCommands::stopMoveRight);
  kb->bindKeyUp(Key::Q, GameCommands::stopMoveLeft);
  kb->bindKeyUp(Key::Z, GameCommands::stopMoveUp);
  kb->bindKeyUp(Key::S, GameCommands::stopMoveDown);
  kb->bindKeyDown(Key::M, GameCommands::exitToMenu);
}

void Game::cleanUp() {
  for (KeyBind* c : commands) {
    if (c) delete c;
  }

  commands.clear();
}

void Game::update(int dt) {
  player.posx += player.vx * dt / 2;
  player.posy += player.vy * dt / 2;
  if (player.posx > 992) player.posx = 992;
  else if (player.posx < 0) player.posx = 0;
  if (player.posy > 736) player.posy = 736;
  else if (player.posy < 0) player.posy = 0;
}

void Game::display(const DisplayManager* dm, const int dt) {
  GameState::display(dm, dt);
  dm->renderTexture(text, 10, 10);
  dm->render();
}


// Private methods

//
