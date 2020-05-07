//
// Created by vikra on 5/1/2020.
//

#include <mylibrary/Player.h>

namespace mylibrary {

Player::Player(b2World* world) {

  const int kWindowScaling = 2;

  b2BodyDef user_body;
  user_body.type = b2_staticBody;
  user_body.position.Set(Conversions::PointsToMeters(
      mylibrary::Conversions::kWindowWidth  / kWindowScaling),
                         Conversions::PointsToMeters(
                             mylibrary::Conversions::kWindowHeight  - kPlayerRadius));

  player_body = world->CreateBody(&user_body);

  b2PolygonShape player_center;
  player_center.SetAsBox(Conversions::PointsToMeters(kPlayerRadius),
                         Conversions::PointsToMeters(kPlayerRadius));
  density = 2.0f;
  player_body->CreateFixture(&player_center, 2.0f);
  player_body->SetUserData(this);
}

Player::~Player() = default;

void Player::SetPlayerTexture(const std::string& texture_file_path) {
  player_texture = cinder::gl::Texture::create(cinder::loadImage(
      cinder::app::loadAsset(texture_file_path)));
}
const cinder::gl::TextureRef& Player::GetPlayerTexture() const {
  return player_texture;
}

}

