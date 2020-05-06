//
// Created by vikra on 5/1/2020.
//

#ifndef FINALPROJECT_MYLIBRARY_METEOR_H
#define FINALPROJECT_MYLIBRARY_METEOR_H

#include <Box2D/Box2D.h>
#include <cinder/Rand.h>
#include <mylibrary/Conversion.h>
#include <cinder/app/AppBase.h>



namespace mylibrary {

class Meteor {

 public:
  explicit Meteor(b2World* world, float radius);
  ~Meteor();
  b2Body* meteor_body;

};

}


#endif  // FINALPROJECT_MYLIBRARY_METEOR_H
