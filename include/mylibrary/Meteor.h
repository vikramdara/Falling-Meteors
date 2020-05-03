//
// Created by vikra on 5/1/2020.
//

#ifndef FINALPROJECT_MYLIBRARY_METEOR_H
#define FINALPROJECT_MYLIBRARY_METEOR_H

#include <Box2D/Box2D.h>
#include <cinder/app/App.h>
#include <cinder/Rand.h>



namespace mylibrary {

class Meteor {

  static constexpr float METERS_TO_POINTS = 200.0f;
  static constexpr float POINTS_TO_METERS = 0.005f;

 public:
  explicit Meteor(b2World* world, float radius);
  ~Meteor();
  b2Body* meteor_body;
  cinder::vec2 pointsToMeters( const cinder::vec2 &var )	{ return var * POINTS_TO_METERS; }
};

}


#endif  // FINALPROJECT_MYLIBRARY_METEOR_H
