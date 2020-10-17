#include "MenuCommands.hpp"

#include <iostream>
#include "Yume/Engine.hpp"

#include "Game.hpp"


using namespace std;


// Init

Engine* MenuCommands::engine = nullptr;

void MenuCommands::init(Engine* e) {
  if (!e) {
    cout << "Link to Engine is needed!" << endl;
  } else {
    engine = e;
  }
}


// Commands

void MenuCommands::enterGame() {
  engine->pushState(new Game());
}
