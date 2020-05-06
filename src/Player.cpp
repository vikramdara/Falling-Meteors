//
// Created by vikra on 5/1/2020.
//

#include <mylibrary/Player.h>

namespace mylibrary {

Player::Player(b2World* world) {
  player_texture = cinder::gl::Texture::create(cinder::loadImage(cinder::app::loadAsset("transparent_player.png")));

  b2BodyDef user_body;
  user_body.type = b2_staticBody;
  user_body.position.Set(Conversions::pointsToMeters(cinder::app::getWindowWidth() / 2), Conversions::pointsToMeters(cinder::app::getWindowHeight() - 25));
  player_body = world->CreateBody(&user_body);

  b2PolygonShape player_center;
  player_center.SetAsBox(Conversions::pointsToMeters(25), Conversions::pointsToMeters(25));
  density = 2.0f;
  player_body->CreateFixture(&player_center, 2.0f);
  player_body->SetUserData(this);
}

Player::~Player() {}

}
