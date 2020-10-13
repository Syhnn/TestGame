#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "Yume/Engine.hpp"
#include "Yume/GameState.hpp"


class Game : public GameState {
public:
  Game();

  void init(DisplayManager* dm) override;
  void cleanUp() override;

  // todo: add KeyBinds class
  //void handleInputs(Engine* engine) override;
  void update() override;
  void display(const DisplayManager* dm) override;

private:
  int tmp;
};

#endif // _GAME_HPP_
