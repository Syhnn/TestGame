#ifndef _MENU_HPP_
#define _MENU_HPP_

#include "Yume/Engine.hpp"
#include "Yume/GameState.hpp"


class Menu : public GameState {
public:
  Menu();

  void init(DisplayManager* dm) override;
  void cleanUp() override;

  void handleInputs(Engine* engine) override;
  void update(int dt) override;
  void display(const DisplayManager* dm, const int dt) override;

private:
  int nextState;
  int text;
};

#endif // _MENU_HPP_
