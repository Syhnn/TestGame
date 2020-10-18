#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include "Yume/Actor.hpp"


class Player : public Actor {
public:
  Player();

  int getClipId(const int dt);

private:
  int pose;
  int frame;

  const int frame_duration;
  int next_frame;
};

#endif // _PLAYER_HPP_
