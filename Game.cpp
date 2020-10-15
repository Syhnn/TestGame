#include "Game.hpp"

#include <iostream>
#include <string>
#include "Yume/DisplayManager.hpp"
#include "Yume/KeyBinds.hpp"


using namespace std;


class MoveRight : public KeyBind {
public:
  MoveRight(Player* p) : player(p) {}

  void callback() override {
    if (player) player->vx += 1;
  }

private:
  Player* player;
};

class MoveLeft : public KeyBind {
public:
  MoveLeft(Player* p) : player(p) {}

  void callback() override {
    if (player) player->vx -= 1;
  }

private:
  Player* player;
};

class MoveUp : public KeyBind {
public:
  MoveUp(Player* p) : player(p) {}

  void callback() override {
    if (player) player->vy -= 1;
  }

private:
  Player* player;
};

class MoveDown : public KeyBind {
public:
  MoveDown(Player* p) : player(p) {}

  void callback() override {
    if (player) player->vy += 1;
  }

private:
  Player* player;
};

class StopMoveRight : public KeyBind {
public:
  StopMoveRight(Player* p) : player(p) {}

  void callback() override {
    if (player) player->vx -= 1;
  }

private:
  Player* player;
};

class StopMoveLeft : public KeyBind {
public:
  StopMoveLeft(Player* p) : player(p) {}

  void callback() override {
    if (player) player->vx += 1;
  }

private:
  Player* player;
};

class StopMoveUp : public KeyBind {
public:
  StopMoveUp(Player* p) : player(p) {}

  void callback() override {
    if (player) player->vy += 1;
  }

private:
  Player* player;
};

class StopMoveDown : public KeyBind {
public:
  StopMoveDown(Player* p) : player(p) {}

  void callback() override {
    if (player) player->vy -= 1;
  }

private:
  Player* player;
};

class ExitToMenu : public KeyBind {
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


  KeyBind* b(nullptr);

  b = new StopMoveUp(&player);
  commands.insert(b);
  kb->bindKeyUp(Key::Z, b);

  b = new StopMoveLeft(&player);
  commands.insert(b);
  kb->bindKeyUp(Key::Q, b);

  b = new StopMoveDown(&player);
  commands.insert(b);
  kb->bindKeyUp(Key::S, b);

  b = new StopMoveRight(&player);
  commands.insert(b);
  kb->bindKeyUp(Key::D, b);

  b = new MoveUp(&player);
  commands.insert(b);
  kb->bindKeyDown(Key::Z, b);

  b = new MoveLeft(&player);
  commands.insert(b);
  kb->bindKeyDown(Key::Q, b);

  b = new MoveDown(&player);
  commands.insert(b);
  kb->bindKeyDown(Key::S, b);

  b = new MoveRight(&player);
  commands.insert(b);
  kb->bindKeyDown(Key::D, b);

  b = new ExitToMenu(e);
  commands.insert(b);
  kb->bindKeyDown(Key::M, b);
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
