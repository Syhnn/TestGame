#include "Game.hpp"

#include <iostream>
#include <string>
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
  }

  path = "assets/2D Pixel Dungeon Asset Pack/character and tileset/Dungeon_Tileset.png";
  tilemapTextureId = dm->loadTexture(path, 16, 16);
  if (tilemapTextureId == -1) {
    cout << "Couldn't load texture " << path << endl;
  } else {
    // Will be replaced with file data import because this is ugly
    int walls_l1 = dm->addTextureClip(tilemapTextureId,  0,  0, 16, 16);
    int walls_r1 = dm->addTextureClip(tilemapTextureId, 80, 16, 16, 16);
    int walls_t1 = dm->addTextureClip(tilemapTextureId, 16,  0, 16, 16);
    int walls_t2 = dm->addTextureClip(tilemapTextureId, 32,  0, 16, 16);
    int walls_t3 = dm->addTextureClip(tilemapTextureId, 48,  0, 16, 16);
    int walls_b1 = dm->addTextureClip(tilemapTextureId, 16, 64, 16, 16);
    int walls_b2 = dm->addTextureClip(tilemapTextureId, 32, 64, 16, 16);
    int walls_bl = dm->addTextureClip(tilemapTextureId,  0, 64, 16, 16);
    int walls_br = dm->addTextureClip(tilemapTextureId, 80, 64, 16, 16);
    int floor_tl = dm->addTextureClip(tilemapTextureId, 16, 16, 16, 16);
    int floor_tr = dm->addTextureClip(tilemapTextureId, 64, 16, 16, 16);
    int floor_t1 = dm->addTextureClip(tilemapTextureId, 32, 16, 16, 16);
    int floor_t2 = dm->addTextureClip(tilemapTextureId, 48, 16, 16, 16);
    int floor_l1 = dm->addTextureClip(tilemapTextureId, 16, 32, 16, 16);
    int floor_r1 = dm->addTextureClip(tilemapTextureId, 64, 32, 16, 16);
    int floor_c1 = dm->addTextureClip(tilemapTextureId, 32, 32, 16, 16);
    int floor_c2 = dm->addTextureClip(tilemapTextureId, 48, 32, 16, 16);
    int floor_bl = dm->addTextureClip(tilemapTextureId, 16, 48, 16, 16);
    int floor_br = dm->addTextureClip(tilemapTextureId, 64, 48, 16, 16);
    int floor_b1 = dm->addTextureClip(tilemapTextureId, 32, 48, 16, 16);
    int floor_b2 = dm->addTextureClip(tilemapTextureId, 48, 48, 16, 16);
    map = new TileMap(8, 6, 32, {{walls_l1, walls_t1, walls_t2, walls_t1, walls_t3, walls_t3, walls_t1, walls_r1},
                                 {walls_l1, floor_tl, floor_t1, floor_t1, floor_t2, floor_t1, floor_tr, walls_r1},
                                 {walls_l1, floor_l1, floor_c2, floor_c2, floor_c1, floor_c2, floor_r1, walls_r1},
                                 {walls_l1, floor_l1, floor_c1, floor_c2, floor_c2, floor_c1, floor_r1, walls_r1},
                                 {walls_l1, floor_bl, floor_b1, floor_b2, floor_b1, floor_b1, floor_br, walls_r1},
                                 {walls_bl, walls_b1, walls_b2, walls_b1, walls_b2, walls_b2, walls_b1, walls_br}});
    map->posx = 384;
    map->posy = 288;
    map->texture_id = tilemapTextureId;
    if (dm->createTextureFromTilemap(map) == -1) {
      cout << "Couldn't generate texture from tilemap" << endl;
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
  if (player->posx > 576) player->posx = 576;
  else if (player->posx < 416) player->posx = 416;
  if (player->posy > 416) player->posy = 416;
  else if (player->posy < 320) player->posy = 320;
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
