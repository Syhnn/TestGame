#include "Menu.hpp"

#include <iostream>
#include <string>
#include "Yume/DisplayManager.hpp"
#include "Yume/KeyBinds.hpp"

#include "Game.hpp"


using namespace std;


// Constructors and destructor

Menu::Menu() :
  GameState(),

  nextState(10),
  text(-1)
{}


// Public methods

void Menu::init(DisplayManager* dm) {
  text = dm->loadText("Main Menu :D");
  if (text == -1) {
    cout << "Couldn't load text" << endl;
  }

  kb->bindKeyUp(Key::N, nextState);
}

void Menu::cleanUp() {

}

void Menu::handleInputs(Engine* engine) {
  GameState::handleInputs(engine);

  vector<int> commands = kb->getEvents();
  for (int command : commands) {
    if (command == nextState) {
      engine->pushState(new Game());
    }
  }
}

void Menu::update(int dt) {
  // nothing
}

void Menu::display(const DisplayManager* dm, const int dt) {
  GameState::display(dm, dt);
  dm->renderTexture(text, 420, 300);
  dm->render();
}


// Private methods

//
