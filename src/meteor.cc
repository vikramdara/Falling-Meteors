// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <mylibrary/meteor.h>
namespace mylibrary {

Meteor::Meteor(b2World* world_) {
  b2BodyDef meteor;
  meteor.type = b2_dynamicBody;
  meteor.allowSleep = false;
  meteor.position.Set( 2, 0 );

  b2CircleShape shape;
  shape.m_radius = 1.0f;

  b2FixtureDef fixtureDef;
  fixtureDef.shape = &shape;
  fixtureDef.density = 1.0f;
  meteor_body = world_->CreateBody(&meteor);
  meteor_body->CreateFixture(&fixtureDef);

}

b2Body* Meteor::GetMeteorBody() {
  return meteor_body;
}

}  // namespace mylibrary
