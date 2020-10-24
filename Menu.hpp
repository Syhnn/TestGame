#ifndef _MENU_HPP_
#define _MENU_HPP_

#include "Yume/Engine.hpp"
#include "Yume/GameState.hpp"


class Menu : public GameState {
public:
  Menu();

  void init(Engine* e, DisplayManager* dm) override;
  void cleanUp() override;

  void update(int dt) override;
  void display(DisplayManager* const dm, const int dt) override;

private:
  int text;
};

#endif // _MENU_HPP_
