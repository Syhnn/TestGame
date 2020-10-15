#include "Menu.hpp"

#include <iostream>
#include <string>
#include "Yume/DisplayManager.hpp"
#include "Yume/KeyBinds.hpp"

#include "Game.hpp"


using namespace std;


class NextState : public KeyBind {
public:
  NextState(Engine* e) : engine(e) {}

  void callback() override {
    if (engine) engine->pushState(new Game());
  }

private:
  Engine* engine;
};


// Constructors and destructor

Menu::Menu() :
  GameState(),

  nextState(nullptr),

  text(-1)
{}


// Public methods

void Menu::init(Engine* e, DisplayManager* dm) {
  text = dm->loadText("Main Menu :D");
  if (text == -1) {
    cout << "Couldn't load text" << endl;
  }

  nextState = new NextState(e);
  kb->bindKeyUp(Key::N, nextState);
}

void Menu::cleanUp() {
  if (nextState) {
    delete nextState;
    nextState = nullptr;
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
