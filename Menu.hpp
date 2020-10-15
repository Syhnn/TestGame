#ifndef _MENU_HPP_
#define _MENU_HPP_

#include "Yume/Engine.hpp"
#include "Yume/GameState.hpp"


class Command;


class Menu : public GameState {
public:
  Menu();

  void init(Engine* e, DisplayManager* dm) override;
  void cleanUp() override;

  void update(int dt) override;
  void display(const DisplayManager* dm, const int dt) override;

private:
  Command* nextState;

  int text;
};

#endif // _MENU_HPP_
