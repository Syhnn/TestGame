#include <iostream>
#include <set>

#include "Yume/Engine.hpp"

#include "Menu.hpp"


using namespace std;


class SomethingCommands {
public:
  static void moveRight() { cout << "move right" << endl; }
};

int main(int argc, char* argv[]) {
  void (*func)();
  func = SomethingCommands::moveRight;
  func();


  Engine e;

  if (!e.init()) {
    cout << "shit happened" << endl;
    return 1;
  }

  Menu m;
  e.pushState(&m);

  e.mainloop();

  return 0;
}