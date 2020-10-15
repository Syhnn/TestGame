#include <iostream>
#include <set>

#include "Yume/Engine.hpp"

#include "Menu.hpp"


using namespace std;


int main(int argc, char* argv[]) {
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