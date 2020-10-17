#include "Menu.hpp"

#include <iostream>
#include <string>
#include "Yume/DisplayManager.hpp"
#include "Yume/KeyBinds.hpp"

#include "MenuCommands.hpp"


using namespace std;


// Constructors and destructor

Menu::Menu() :
  GameState(),

  text(-1)
{}


// Public methods

void Menu::init(Engine* e, DisplayManager* dm) {
  text = dm->loadText("Main Menu :D");
  if (text == -1) {
    cout << "Couldn't load text" << endl;
  }

  MenuCommands::init(e);
  kb->bindKeyDown(Key::N, MenuCommands::enterGame);
}

void Menu::cleanUp() {
  //
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
