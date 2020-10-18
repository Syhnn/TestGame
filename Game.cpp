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
    int left_wall = dm->addTextureClip(tilemapTextureId, 0, 0, 16, 16);
    int right_wall = dm->addTextureClip(tilemapTextureId, 80, 16, 16, 16);
    int top_wall = dm->addTextureClip(tilemapTextureId, 16, 0, 16, 16);
    int bottom_wall = dm->addTextureClip(tilemapTextureId, 16, 64, 16, 16);
    int bl_corner = dm->addTextureClip(tilemapTextureId, 0, 64, 16, 16);
    int br_corner = dm->addTextureClip(tilemapTextureId, 80, 64, 16, 16);
    int floor = dm->addTextureClip(tilemapTextureId, 16, 16, 16, 16);
    map = new TileMap(8, 6, 32, { {left_wall, top_wall, top_wall, top_wall, top_wall, top_wall, top_wall, right_wall},
                                  {left_wall, floor, floor, floor, floor, floor, floor, right_wall},
                                  {left_wall, floor, floor, floor, floor, floor, floor, right_wall},
                                  {left_wall, floor, floor, floor, floor, floor, floor, right_wall},
                                  {left_wall, floor, floor, floor, floor, floor, floor, right_wall},
                                  {bl_corner, bottom_wall, bottom_wall, bottom_wall, bottom_wall, bottom_wall, bottom_wall, br_corner}});
    map->posx = 384;
    map->posy = 288;
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
  //GameState::display(dm, dt);
  dm->clear();
  dm->renderTileMap(tilemapTextureId, map->posx, map->posy, map);
  dm->renderTexture(textTextureId, 10, 10);
  dm->renderClip(player->texture_id, player->posx, player->posy, player->getClipId(dt));
  dm->render();
}


// Private methods

//
