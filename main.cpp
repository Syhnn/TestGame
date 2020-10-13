#include <iostream>
#include <set>

#include "Yume/Engine.hpp"

#include "Game.hpp"


using namespace std;


int main(int argc, char* argv[]) {
  Engine e;

  if (!e.init()) {
    cout << "shit happened" << endl;
    return 1;
  }

  Game g;
  e.pushState(&g);

  e.mainloop();

  return 0;
}