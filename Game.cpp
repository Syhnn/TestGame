#include "Game.hpp"

#include <iostream>
#include <map>
#include <string>
#include "Yume/DataLoader.hpp"
#include "Yume/DisplayManager.hpp"
#include "Yume/KeyBinds.hpp"
#include "Yume/TileMap.hpp"

#include "GameCommands.hpp"
#include "player.hpp"


using namespace std;


// Constructors and destructor

Game::Game() :
  GameState(),

  textTextureId(-1),
  playerTextureId(-1),
  tilemapTextureId(-1),

  player(nullptr),
  tilemap(nullptr)
{}


// Public methods

void Game::init(Engine* e, DisplayManager* dm) {
  // import assets
  map<string, Entity*> ent = DataLoader::loadStateData(dm, "assets/json/game_data.json");

  int playerTextureId = dm->getTextureId("test_char");
  if (playerTextureId == -1) {
    cout << "Couldn't find texture " << endl;
    e->exit();
  } else {
    player = new Player();
    player->posx = 496;
    player->posy = 368;
    player->texture_id = playerTextureId;
    addEntity(player);
  }

  textTextureId = dm->loadText("abcdefghijklmnopqrstuvwxyz");
  if (textTextureId == -1) {
    cout << "Couldn't load text" << endl;
    e->exit();
  }

  if (ent.find("level_1_tilemap") == ent.end()) {
    cout << "couldn't find tilemap in imported data" << endl;
    e->exit();
  } else {
    tilemap = dynamic_cast<TileMap*>(ent["level_1_tilemap"]);
  }
  
  GameCommands::init(e, player);
  kb->bindKeyDown(Key::D, GameCommands::moveRight);
  kb->bindKeyDown(Key::Q, GameCommands::moveLeft);
  kb->bindKeyDown(Key::Z, GameCommands::moveUp);
  kb->bindKeyDown(Key::S, GameCommands::moveDown);
  kb->bindKeyUp(Key::D, GameCommands::stopMoveRight);
  kb->bindKeyUp(Key::Q, GameCommands::stopMoveLeft);
  kb->bindKeyUp(Key::Z, GameCommands::stopMoveUp);
  kb->bindKeyUp(Key::S, GameCommands::stopMoveDown);
  kb->bindKeyDown(Key::M, GameCommands::exitToMenu);

  dm->setClearColor(0x25, 0x13, 0x1A);
}

void Game::cleanUp() {
  if (player) {
    delete player;
    player = nullptr;
  }

  if (tilemap) {
    delete tilemap;
    tilemap = nullptr;
  }
}

void Game::update(int dt) {
  player->posx += player->vx * dt / 2;
  player->posy += player->vy * dt / 2;
  if (player->posx > 960) player->posx = 960;
  else if (player->posx < 32) player->posx = 32;
  if (player->posy > 704) player->posy = 704;
  else if (player->posy < 32) player->posy = 32;
}

void Game::display(DisplayManager* const dm, const int dt) {
  dm->clear();
  dm->renderTexture(tilemap->fixed_texture_id, tilemap->posx, tilemap->posy);
  dm->renderTexture(textTextureId, 10, 10);
  dm->renderClip(player->texture_id, player->posx, player->posy, player->getClipId(dt));
  dm->render();
}


// Private methods

//
