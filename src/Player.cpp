//
// Created by vikra on 5/1/2020.
//

#include <mylibrary/Player.h>

namespace mylibrary {

Player::Player(b2World* world) {
  b2BodyDef user_body;
  user_body.type = b2_staticBody;
  user_body.position.Set(mylibrary::Conversions::pointsToMeters(cinder::app::getWindowWidth() / 2), mylibrary::Conversions::pointsToMeters(cinder::app::getWindowHeight() - 25));
  player_body = world->CreateBody(&user_body);

  b2PolygonShape player_center;
  player_center.SetAsBox(mylibrary::Conversions::pointsToMeters(25), mylibrary::Conversions::pointsToMeters(25));
  density = 2.0f;
  player_body->CreateFixture(&player_center, 2.0f);
  player_body->SetUserData(this);
}

Player::~Player() {}

}
