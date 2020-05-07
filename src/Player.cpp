//
// Created by vikra on 5/1/2020.
//

#include <mylibrary/Player.h>

namespace mylibrary {

Player::Player(b2World* world) {
  player_texture = cinder::gl::Texture::create(cinder::loadImage(
      cinder::app::loadAsset("transparent_player.png")));

  const int kWindowScaling = 2;

  b2BodyDef user_body;
  user_body.type = b2_staticBody;
  user_body.position.Set(Conversions::PointsToMeters(
                             cinder::app::getWindowWidth() / kWindowScaling),
                         Conversions::PointsToMeters(
                             cinder::app::getWindowHeight() - kPlayerRadius));

  player_body = world->CreateBody(&user_body);

  b2PolygonShape player_center;
  player_center.SetAsBox(Conversions::PointsToMeters(kPlayerRadius),
                         Conversions::PointsToMeters(kPlayerRadius));
  density = 2.0f;
  player_body->CreateFixture(&player_center, 2.0f);
  player_body->SetUserData(this);
}

Player::~Player() = default;

}
