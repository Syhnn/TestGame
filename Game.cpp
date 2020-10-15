#include "Game.hpp"

#include <iostream>
#include <string>
#include "Yume/DisplayManager.hpp"
#include "Yume/KeyBinds.hpp"
#include "Yume/Command.hpp"


using namespace std;


class MoveRight : public Command {
public:
  MoveRight(Player* p) : player(p) {}

  void callback() override {
    if (player) player->vx += 1;
  }

private:
  Player* player;
};

class MoveLeft : public Command {
public:
  MoveLeft(Player* p) : player(p) {}

  void callback() override {
    if (player) player->vx -= 1;
  }

private:
  Player* player;
};

class MoveUp : public Command {
public:
  MoveUp(Player* p) : player(p) {}

  void callback() override {
    if (player) player->vy -= 1;
  }

private:
  Player* player;
};

class MoveDown : public Command {
public:
  MoveDown(Player* p) : player(p) {}

  void callback() override {
    if (player) player->vy += 1;
  }

private:
  Player* player;
};

class StopMoveRight : public Command {
public:
  StopMoveRight(Player* p) : player(p) {}

  void callback() override {
    if (player) player->vx -= 1;
  }

private:
  Player* player;
};

class StopMoveLeft : public Command {
public:
  StopMoveLeft(Player* p) : player(p) {}

  void callback() override {
    if (player) player->vx += 1;
  }

private:
  Player* player;
};

class StopMoveUp : public Command {
public:
  StopMoveUp(Player* p) : player(p) {}

  void callback() override {
    if (player) player->vy += 1;
  }

private:
  Player* player;
};

class StopMoveDown : public Command {
public:
  StopMoveDown(Player* p) : player(p) {}

  void callback() override {
    if (player) player->vy -= 1;
  }

private:
  Player* player;
};

class ExitToMenu : public Command {
public:
  ExitToMenu(Engine* e) : engine(e) {}

  void callback() override {
    if (engine) engine->popState();
  }

private:
  Engine* engine;
};

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


  Command* c(nullptr);

  c = new StopMoveUp(&player);
  commands.insert(c);
  kb->bindKeyUp(Key::Z, c);

  c = new StopMoveLeft(&player);
  commands.insert(c);
  kb->bindKeyUp(Key::Q, c);

  c = new StopMoveDown(&player);
  commands.insert(c);
  kb->bindKeyUp(Key::S, c);

  c = new StopMoveRight(&player);
  commands.insert(c);
  kb->bindKeyUp(Key::D, c);

  c = new MoveUp(&player);
  commands.insert(c);
  kb->bindKeyDown(Key::Z, c);

  c = new MoveLeft(&player);
  commands.insert(c);
  kb->bindKeyDown(Key::Q, c);

  c = new MoveDown(&player);
  commands.insert(c);
  kb->bindKeyDown(Key::S, c);

  c = new MoveRight(&player);
  commands.insert(c);
  kb->bindKeyDown(Key::D, c);

  c = new ExitToMenu(e);
  commands.insert(c);
  kb->bindKeyDown(Key::M, c);
}

void Game::cleanUp() {
  for (Command* c : commands) {
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
