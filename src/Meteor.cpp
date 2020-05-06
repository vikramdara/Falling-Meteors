//
// Created by vikra on 5/1/2020.
//

#include <mylibrary/Meteor.h>

namespace mylibrary {

Meteor::Meteor(b2World* world, const float kRadius, const mylibrary::Wave& kWave, double seconds) {
  meteor_texture = cinder::gl::Texture::create(cinder::loadImage(cinder::app::loadAsset("transparent_meteor.png")));

  const float kCinderRadius = mylibrary::Conversions::MetersToPoints(kRadius);
  const float kPositionRange = 200;
  const float kVerticalPositionScale = 2;

  cinder::randSeed(std::time(nullptr));
  cinder::vec2 pos = cinder::vec2(cinder::randFloat(kPositionRange,
      cinder::app::getWindowWidth() - kPositionRange),
          cinder::randFloat( -kCinderRadius,
              -kPositionRange / kVerticalPositionScale));
  cinder::vec2 posScaled = Conversions::pointsToMeters( pos );

  b2BodyDef meteor;
  meteor.type = b2_dynamicBody;

  float velocity_maximum = 2;
  float velocity_minimum = -2;
  meteor.linearVelocity = b2Vec2( cinder::randFloat(velocity_minimum, velocity_maximum), cinder::randFloat( -velocity_minimum, 0 ) );

  if (kWave == mylibrary::Wave::kWaveFour) {
    ChangeStartingPointOfMeteor(meteor, kWave, seconds, posScaled, kCinderRadius);
  }

  meteor.position.Set(posScaled.x, posScaled.y);

  meteor_body = world->CreateBody(&meteor);

  b2CircleShape shape;
  shape.m_radius = kRadius;

  b2FixtureDef fixtureDef;
  fixtureDef.shape = &shape;
  fixtureDef.density = 1.0f;
  fixtureDef.friction = 1.0f;
  fixtureDef.restitution = 0.4f;

  meteor_body->CreateFixture(&fixtureDef);
  meteor_body->SetUserData(this);
}

void Meteor::ChangeStartingPointOfMeteor(b2BodyDef& meteor,
    const mylibrary::Wave& kWave,
    double seconds,
    cinder::vec2& starting_position,
    const float kCinderRadius) {
  cinder::randSeed(std::time(nullptr));

  const int kSecondsForPositionChange = 5;
  const int kScaleRadius = 2;
  const int kScaleWindow = 2;

  float velocity_maximum;
  float velocity_minimum;

  cinder::vec2 pos;
  cinder::vec2 posScaled;

  switch (static_cast<int>(std::floor(seconds) / kSecondsForPositionChange)) {
    case 0:
      pos = cinder::vec2(cinder::randFloat(cinder::app::getWindowWidth() + kCinderRadius, cinder::app::getWindowWidth() + kCinderRadius * kScaleRadius),
                         cinder::randFloat( 0, cinder::app::getWindowHeight() / kScaleWindow));
      starting_position = Conversions::pointsToMeters( pos );

      velocity_minimum = -10;
      velocity_maximum = -3;
      meteor.linearVelocity = b2Vec2( cinder::randFloat(velocity_minimum, velocity_maximum), cinder::randFloat( 0, -velocity_maximum) );
      break;
    case 1:
      return;
    case 2:
      pos = cinder::vec2(cinder::randFloat(-kCinderRadius * kScaleRadius, -kCinderRadius),
                         cinder::randFloat( 0, cinder::app::getWindowHeight() / kScaleWindow));
      starting_position = Conversions::pointsToMeters( pos );

      velocity_minimum = 3;
      velocity_maximum = 10;
      meteor.linearVelocity = b2Vec2( cinder::randFloat(velocity_minimum, velocity_maximum), cinder::randFloat( 0, velocity_minimum) );
      break;
  }
}

}
