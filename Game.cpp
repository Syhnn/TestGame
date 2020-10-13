#include "Game.hpp"

#include <iostream>
#include <string>
#include "Yume/DisplayManager.hpp"


using namespace std;


// Constructors and destructor

Game::Game() :
  tmp(-1)
{}


// Public methods

void Game::init(DisplayManager* dm) {
  string path = "assets/culture.png";
  tmp = dm->loadTexture(path, 383, 501);
  if (tmp == -1) {
    cout << "Couldn't load texture " << path << endl;
  }
}

void Game::cleanUp() {

}

void Game::update() {

}

void Game::display(const DisplayManager* dm) {
  dm->clear();
  dm->renderTexture(tmp, 0, 0);
  dm->render();
}


// Private methods

//
