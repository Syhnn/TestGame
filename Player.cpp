#include "Player.hpp"

#include "Yume/Engine.hpp"


using namespace std;


// Constructors and destructor

Player::Player() :
  Entity(),

  pose(0),
  frame(0),

  frame_duration(120),
  next_frame(frame_duration)
{}


// Public methods

int Player::getClipId(const int dt) {
  next_frame -= dt;
  if (next_frame < 0) {
    next_frame += frame_duration;
    ++frame;
    if (frame >= 4) frame = 0;
  }

  if (vx == 0 && vy == 0) return 0;

  if (vx > 0) {
    pose = 2;
  } else if (vx < 0) {
    pose = 1;
  }

  if (vy > 0) {
    pose = 0;
  } else if (vy < 0) {
    pose = 3;
  }

  return pose * 4 + frame;
}


// Private methods

//
