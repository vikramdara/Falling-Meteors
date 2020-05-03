//
// Created by vikra on 5/1/2020.
//

#ifndef FINALPROJECT_MYLIBRARY_PLAYER_H
#define FINALPROJECT_MYLIBRARY_PLAYER_H

#include <Box2D/Box2D.h>
#include <cinder/app/App.h>

namespace mylibrary {

class Player {
  static constexpr float METERS_TO_POINTS = 200.0f;
  static constexpr float POINTS_TO_METERS = 0.005f;

 public:
  explicit Player(b2World* world);
  ~Player();
  b2Body* player_body;
  float density;
  cinder::vec2 pointsToMeters( const cinder::vec2 &var )	{ return var * POINTS_TO_METERS; }
  float pointsToMeters( float var )			{ return var * POINTS_TO_METERS; }


};

}

#endif  // FINALPROJECT_PLAYER_H
