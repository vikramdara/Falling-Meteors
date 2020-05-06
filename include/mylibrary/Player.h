//
// Created by vikra on 5/1/2020.
//

#ifndef FINALPROJECT_MYLIBRARY_PLAYER_H
#define FINALPROJECT_MYLIBRARY_PLAYER_H

#include <Box2D/Box2D.h>
#include <cinder/app/AppBase.h>
#include <cinder/gl/Texture.h>
#include <mylibrary/Conversion.h>

namespace mylibrary {

class Player {

 public:
  explicit Player(b2World* world);
  ~Player();

  b2Body* player_body;
  cinder::gl::TextureRef player_texture;
  float density;
  const float kPlayerRadius = 25;

};

}

#endif  // FINALPROJECT_PLAYER_H
