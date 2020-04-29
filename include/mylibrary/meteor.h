// Copyright (c) 2020 [Your Name]. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_EXAMPLE_H_
#define FINALPROJECT_MYLIBRARY_EXAMPLE_H_
#include <Box2D/Box2D.h>
#include <cinder/Rand.h>

namespace mylibrary {

class Meteor {
 public:
  explicit Meteor(b2World* world_);

  b2Body* GetMeteorBody();
 private:
  b2Body* meteor_body;
};

}  // namespace mylibrary


#endif // FINALPROJECT_MYLIBRARY_EXAMPLE_H_
