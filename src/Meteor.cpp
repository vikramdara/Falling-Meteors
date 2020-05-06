//
// Created by vikra on 5/1/2020.
//

#include <mylibrary/Meteor.h>

namespace mylibrary {

Meteor::Meteor(b2World* world, float radius, mylibrary::Wave wave) {
  cinder::randSeed(std::time(nullptr));
  cinder::vec2 pos = cinder::vec2(cinder::randFloat(200, cinder::app::getWindowWidth() - 200), cinder::randFloat( -40, -100));
  cinder::vec2 posScaled = mylibrary::Conversions::pointsToMeters( pos );

  b2BodyDef meteor;
  meteor.type = b2_dynamicBody;

  const float velMax = 2;
  meteor.linearVelocity = b2Vec2( cinder::randFloat( -velMax, velMax ), cinder::randFloat( -velMax, 0 ) );

  switch (static_cast<int>(std::floor(timer.getSeconds())) / 5) {
    case 0:
      pos = cinder::vec2(cinder::randFloat(cinder::app::getWindowWidth() + 40, cinder::app::getWindowWidth() + 80),
          cinder::randFloat( 0, cinder::app::getWindowHeight() / 2));
      posScaled = mylibrary::Conversions::pointsToMeters( pos );
      meteor.linearVelocity = b2Vec2( cinder::randFloat( -100, -30 ), cinder::randFloat( 0, 30 ) );
      break;
    case 2:
      pos = cinder::vec2(cinder::randFloat(-80, -40),
          cinder::randFloat( 0, cinder::app::getWindowHeight() / 2));
      posScaled = mylibrary::Conversions::pointsToMeters( pos );
      meteor.linearVelocity = b2Vec2( cinder::randFloat( 30, 100 ), cinder::randFloat( 0, 30 ) );
      break;
  }


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

Meteor::~Meteor() {

}

}
