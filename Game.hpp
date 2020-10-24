#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <set>

#include "Yume/Engine.hpp"
#include "Yume/GameState.hpp"


class Player;
class TileMap;

enum CommandNames { move_right, move_left, move_up, move_down, stop_move_right, stop_move_left, stop_move_up, stop_move_down, exit_to_menu };


class Game : public GameState {
public:
  Game();

  void init(Engine* e, DisplayManager* dm) override;
  void cleanUp() override;

  void update(int dt) override;
  void display(DisplayManager* const dm, const int dt) override;

private:
  Player* player;
  TileMap* map;

  int textTextureId;
  int playerTextureId;
  int tilemapTextureId;
};

#endif // _GAME_HPP_
