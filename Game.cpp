#include "Game.hpp"

#include <iostream>
#include <string>
#include "Yume/DisplayManager.hpp"
#include "Yume/KeyBinds.hpp"


using namespace std;


// Constructors and destructor

Game::Game()
  //
{}


// Public methods

void Game::init(DisplayManager* dm, KeyBinds* kb) {
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

  kb->bindKeyUp(Key::Z, CommandNames::stop_move_up);
  kb->bindKeyUp(Key::Q, CommandNames::stop_move_left);
  kb->bindKeyUp(Key::S, CommandNames::stop_move_down);
  kb->bindKeyUp(Key::D, CommandNames::stop_move_right);
  kb->bindKeyDown(Key::Z, CommandNames::move_up);
  kb->bindKeyDown(Key::Q, CommandNames::move_left);
  kb->bindKeyDown(Key::S, CommandNames::move_down);
  kb->bindKeyDown(Key::D, CommandNames::move_right);
}

void Game::cleanUp() {

}

void Game::handleInputs(KeyBinds* kb) {
  vector<int> commands = kb->getEvents();
  for (int c : commands) {
    switch(c) {
      case CommandNames::move_left:
        player.vx -= 1;
        break;
      case CommandNames::move_right:
        player.vx += 1;
        break;
      case CommandNames::move_up:
        player.vy -= 1;
        break;
      case CommandNames::move_down:
        player.vy += 1;
        break;
      case CommandNames::stop_move_left:
        player.vx += 1;
        break;
      case CommandNames::stop_move_right:
        player.vx -= 1;
        break;
      case CommandNames::stop_move_up:
        player.vy += 1;
        break;
      case CommandNames::stop_move_down:
        player.vy -= 1;
        break;
    }
  }
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
