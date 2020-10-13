#include "Game.hpp"

#include <iostream>
#include <string>
#include "Yume/DisplayManager.hpp"


using namespace std;


// Constructors and destructor

Game::Game()
  //
{}


// Public methods

void Game::init(DisplayManager* dm) {
  string path = "assets/culture.png";
  int tmp = dm->loadTexture(path, 383, 501);
  if (tmp == -1) {
    cout << "Couldn't load texture " << path << endl;
  }

  test.textureId = tmp;
  addEntity(&test);
}

void Game::cleanUp() {

}

void Game::update() {

}

void Game::display(const DisplayManager* dm) {
  GameState::display(dm);
  dm->render();
}


// Private methods

//
