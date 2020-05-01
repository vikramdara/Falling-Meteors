//
// Created by vikra on 5/1/2020.
//

#include "mylibrary/Meteor.h"

namespace mylibrary {

Meteor::Meteor(b2World* world, float radius) {
  cinder::vec2 pos = cinder::vec2(cinder::randFloat(0, cinder::app::getWindowWidth()), cinder::randFloat( -40, -100));
  cinder::vec2 posScaled = pointsToMeters( pos );
  b2BodyDef meteor;
  meteor.type = b2_dynamicBody;
  meteor.position.Set(posScaled.x, posScaled.y);
  meteor_body = world->CreateBody(&meteor);

  b2CircleShape shape;
  shape.m_radius = radius;

  b2FixtureDef fixtureDef;
  fixtureDef.shape = &shape;
  fixtureDef.density = 1.0f;
  fixtureDef.friction = 1.0f;
  fixtureDef.restitution = 0.4f;

  meteor_body->CreateFixture(&fixtureDef);
  meteor_body->SetUserData(this);
}
Meteor::~Meteor() {}

}
