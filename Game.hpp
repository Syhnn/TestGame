#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "Yume/Engine.hpp"
#include "Yume/GameState.hpp"
#include "Yume/Entity.hpp"


enum CommandNames { move_right, move_left, move_up, move_down, stop_move_right, stop_move_left, stop_move_up, stop_move_down };


class Game : public GameState {
public:
  Game();

  void init(DisplayManager* dm, KeyBinds* kb) override;
  void cleanUp() override;

  void handleInputs(KeyBinds* kb) override;
  void update(int dt) override;
  void display(const DisplayManager* dm) override;

private:
  Entity test;
};

#endif // _GAME_HPP_
