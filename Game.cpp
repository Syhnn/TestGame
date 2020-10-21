#include "Game.hpp"

#include <iostream>
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
  map(nullptr)
{}


// Public methods

void Game::init(Engine* e, DisplayManager* dm) {
  // import assets
  string path = "assets/testchar.png";
  int playerTextureId = dm->loadTexture(path, 32, 32);
  if (playerTextureId == -1) {
    cout << "Couldn't load texture " << path << endl;
    e->exit();
  } else {
    for (int pose(0); pose < 4; ++pose) {
      for (int frame(0); frame < 4; ++frame) {
        dm->addTextureClip(playerTextureId, frame * 32, pose * 32, 32, 32);
      }
    }

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

  path = "assets/json/tileset.json";
  tilemapTextureId = DataLoader::initTextureFromTileset(dm, path);
  if (tilemapTextureId == -1) {
    cout << "Couldn't load texture from json" << path << endl;
    e->exit();
  } else {
    path = "assets/json/tilemap.json";
    map = DataLoader::initTileMapFromJSON(path, tilemapTextureId);
    if (!map) {
      cout << "Couldn't initialize TileMap from json" << endl;
      e->exit();
    } else {
      map->posx = 0;
      map->posy = 0;
      map->texture_id = tilemapTextureId;
      if (dm->createTextureFromTilemap(map) == -1) {
        cout << "Couldn't generate texture from tilemap" << endl;
        e->exit();
      }
    }
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
  for (KeyBind* c : commands) {
    if (c) delete c;
  }

  commands.clear();

  if (player) {
    delete player;
    player = nullptr;
  }

  if (map) {
    delete map;
    map = nullptr;
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

void Game::display(const DisplayManager* dm, const int dt) {
  dm->clear();
  dm->renderTexture(map->fixed_texture_id, map->posx, map->posy);
  dm->renderTexture(textTextureId, 10, 10);
  dm->renderClip(player->texture_id, player->posx, player->posy, player->getClipId(dt));
  dm->render();
}


// Private methods

//
