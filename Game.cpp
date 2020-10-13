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
  string path = "assets/culture.png";
  int tmp = dm->loadTexture(path, 383, 501);
  if (tmp == -1) {
    cout << "Couldn't load texture " << path << endl;
  }

  // create entities
  test.texture_id = tmp;
  addEntity(&test);

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
        test.vx -= 1;
        break;
      case CommandNames::move_right:
        test.vx += 1;
        break;
      case CommandNames::move_up:
        test.vy -= 1;
        break;
      case CommandNames::move_down:
        test.vy += 1;
        break;
      case CommandNames::stop_move_left:
        test.vx += 1;
        break;
      case CommandNames::stop_move_right:
        test.vx -= 1;
        break;
      case CommandNames::stop_move_up:
        test.vy += 1;
        break;
      case CommandNames::stop_move_down:
        test.vy -= 1;
        break;
    }
  }
}

void Game::update(int dt) {
  cout << "posx : " << test.posx << " - posy : " << test.posy << " - vx : " << test.vx << " - vy : " << test.vy << endl;
  test.posx += test.vx * dt / 2;
  test.posy += test.vy * dt / 2;
  if (test.posx > 641) test.posx = 641;
  else if (test.posx < 0) test.posx = 0;
  if (test.posy > 267) test.posy = 267;
  else if (test.posy < 0) test.posy = 0;
}

void Game::display(const DisplayManager* dm) {
  GameState::display(dm);
  dm->render();
}


// Private methods

//
