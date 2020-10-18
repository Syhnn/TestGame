#ifndef _GAME_COMMANDS_HPP_
#define _GAME_COMMANDS_HPP_


class Engine;
class Player;


class GameCommands {
public:
  static void init(Engine* e, Player* p);

  static void moveLeft();
  static void stopMoveLeft();
  static void moveRight();
  static void stopMoveRight();
  static void moveUp();
  static void stopMoveUp();
  static void moveDown();
  static void stopMoveDown();
  static void exitToMenu();

private:
  static Engine* engine;
  static Player* player;
};

#endif // _GAME_COMMANDS_HPP_
