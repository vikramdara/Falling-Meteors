//
// Created by vikra on 5/1/2020.
//

#include <mylibrary/Meteor.h>

namespace mylibrary {

Meteor::Meteor(b2World* world, float radius, mylibrary::Wave wave) {
  cinder::vec2 pos = cinder::vec2(cinder::randFloat(200, cinder::app::getWindowWidth() - 200), cinder::randFloat( -40, -100));
  cinder::vec2 posScaled = mylibrary::Conversions::pointsToMeters( pos );
  b2BodyDef meteor;
  meteor.type = b2_dynamicBody;
  meteor.position.Set(posScaled.x, posScaled.y);
  cinder::randSeed(std::time(nullptr));
  const float velMax = 2;
  meteor.linearVelocity = b2Vec2( cinder::randFloat( -velMax, velMax ), cinder::randFloat( -velMax, 0 ) );

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

Meteor::~Meteor() {

}

}
