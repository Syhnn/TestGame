#ifndef _MENU_COMMANDS_HPP_
#define _MENU_COMMANDS_HPP_


class Engine;


class MenuCommands {
public:
  static void init(Engine* e);

  static void enterGame();

private:
  static Engine* engine;
};

#endif // _MENU_COMMANDS_HPP_
