#include <iostream>

#include "Yume/Engine.hpp"


using namespace std;


int main(int argc, char* argv[]) {
  Engine e;

  if (!e.init()) {
    cout << "shit happened" << endl;
    return 1;
  }

  e.mainloop();

  return 0;
}