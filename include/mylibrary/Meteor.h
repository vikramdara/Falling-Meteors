//
// Created by vikra on 5/1/2020.
//

#ifndef FINALPROJECT_MYLIBRARY_METEOR_H
#define FINALPROJECT_MYLIBRARY_METEOR_H

#include <Box2D/Box2D.h>
#include <cinder/Rand.h>
#include <cinder/app/AppBase.h>
#include <cinder/gl/Texture.h>
#include <mylibrary/Conversion.h>
#include <mylibrary/Wave.h>

namespace mylibrary {

class Meteor {

 public:
  explicit Meteor(b2World* world,
      float radius,
      const mylibrary::Wave& wave,
      double seconds);

  b2Body* meteor_body;
  cinder::gl::TextureRef meteor_texture;

 private:
  void ChangeStartingPointOfMeteor(b2BodyDef& meteor,
      const mylibrary::Wave& kWave,
      double seconds,
      cinder::vec2& starting_position,
      float kCinderRadius);
};

}


#endif  // FINALPROJECT_MYLIBRARY_METEOR_H
