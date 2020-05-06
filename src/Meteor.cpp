//
// Created by vikra on 5/1/2020.
//

#include <mylibrary/Meteor.h>

namespace mylibrary {

Meteor::Meteor(b2World* world, float radius, mylibrary::Wave wave, double seconds) {
  meteor_texture = cinder::gl::Texture::create(cinder::loadImage(cinder::app::loadAsset("transparent_meteor.png")));

  cinder::randSeed(std::time(nullptr));
  cinder::vec2 pos = cinder::vec2(cinder::randFloat(200, cinder::app::getWindowWidth() - 200), cinder::randFloat( -40, -100));
  cinder::vec2 posScaled = Conversions::pointsToMeters( pos );

  b2BodyDef meteor;
  meteor.type = b2_dynamicBody;

  const float velMax = 2;
  meteor.linearVelocity = b2Vec2( cinder::randFloat( -velMax, velMax ), cinder::randFloat( -velMax, 0 ) );

  if (wave == mylibrary::Wave::kWaveFour) {
    switch (static_cast<int>(std::floor(seconds) / 2)) {
      case 0:
        pos = cinder::vec2(cinder::randFloat(cinder::app::getWindowWidth() + 40, cinder::app::getWindowWidth() + 80),
                           cinder::randFloat( 0, cinder::app::getWindowHeight() / 2));
        posScaled = Conversions::pointsToMeters( pos );
        meteor.linearVelocity = b2Vec2( cinder::randFloat( -10, -3 ), cinder::randFloat( 0, 3 ) );
        break;
      case 2:
        pos = cinder::vec2(cinder::randFloat(-80, -40),
                           cinder::randFloat( 0, cinder::app::getWindowHeight() / 2));
        posScaled = Conversions::pointsToMeters( pos );
        meteor.linearVelocity = b2Vec2( cinder::randFloat( 3, 10 ), cinder::randFloat( 0, 3 ) );
        break;
    }
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
