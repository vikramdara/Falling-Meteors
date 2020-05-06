// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/Rand.h>
#include <cinder/app/App.h>

namespace myapp {

using cinder::app::KeyEvent;

MyApp::MyApp() {
}

void MyApp::setup() {
  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();
  engine_.setup();
}

void MyApp::update() {
  engine_.update();
}

void MyApp::draw() {
  cinder::gl::clear();
  if (engine_.has_proper_contact_occured) {
    DrawGameOver();
    DrawReplayButton();
    return;
  }
  //DrawGround();
  cinder::gl::pushMatrices();

  for (int x = 0; x < engine_.GetMeteors().size(); x++) {
    DrawMeteor(engine_.GetMeteors()[x]);
  }

  DrawPlayer();
  cinder::gl::popMatrices();
}

void MyApp::DrawMeteor(mylibrary::Meteor meteor) {
  cinder::vec2 position_vector = cinder::vec2(meteor.meteor_body->GetPosition().x,
      meteor.meteor_body->GetPosition().y) * METERS_TO_POINTS;
  cinder::gl::ScopedModelMatrix modelScope;
  cinder::gl::translate(position_vector);
  cinder::gl::color(1,0,0);
  cinder::gl::drawSolidCircle(position_vector,
      (meteor.meteor_body->GetFixtureList()->GetShape()->m_radius) * (METERS_TO_POINTS * 2),
      50);
}

void MyApp::DrawGround() {
  cinder::gl::color(0,1,1);
  cinder::Rectf ground_rect(0,
                          cinder::app::getWindowHeight() - 100,
                          cinder::app::getWindowWidth() + 0,
                          cinder::app::getWindowHeight() + 0);
  cinder::gl::drawSolidRect(ground_rect);
}

void MyApp::DrawPlayer() {
  cinder::gl::color(1,0,1);
  mylibrary::Player* player = engine_.GetPlayer();
  cinder::vec2 position_vector = cinder::vec2(player->player_body->GetPosition().x, player->player_body->GetPosition().y) * (METERS_TO_POINTS * 2);
  cinder::Rectf player_rect(position_vector.x - 25,
      position_vector.y - 25,
      position_vector.x + 25,
      position_vector.y + 25);
  cinder::gl::drawSolidRect(player_rect);
}

void MyApp::DrawGameOver() {
  cinder::gl::clear(cinder::Color(0.3, 0.4, 0.5));
  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {500, 100};
  const cinder::Color color = cinder::Color::black();

  auto box = cinder::TextBox()
      .alignment(cinder::TextBox::CENTER)
      .font(cinder::Font("Arial", 80))
      .size(size)
      .color(color)
      .backgroundColor(cinder::ColorA(0, 0, 0, 0))
      .text("Game Over!!");

  const auto box_size = box.getSize();
  const cinder::vec2 locp = {center.x - box_size.x / 2, center.y - box_size.y / 2};
  const auto surface = box.render();
  const auto texture = cinder::gl::Texture::create(surface);
  cinder::gl::draw(texture, locp);
}

void MyApp::DrawReplayButton() {
  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {400, 100};
  const cinder::Color color = cinder::Color::black();

  auto box = cinder::TextBox()
      .alignment(cinder::TextBox::CENTER)
      .font(cinder::Font("Arial", 80))
      .size(size)
      .color(color)
      .backgroundColor(cinder::ColorA(0.4, 0, 0, 1))
      .text("Replay Game");

  const auto box_size = box.getSize();
  const cinder::vec2 locp = {center.x - box_size.x / 2, (center.y - box_size.y / 2) + 200};
  const auto surface = box.render();
  const auto texture = cinder::gl::Texture::create(surface);
  cinder::gl::draw(texture, locp);
}

void MyApp::ReplayGame(const cinder::vec2& position) {
  if ((position.x < 600 || position.x > 200)
  && (position.y < 650 || position.y > 550)) {
    engine_.reset();
    setup();
  }
}

void MyApp::keyDown(KeyEvent event) {
  switch (event.getCode()) {
    case KeyEvent::KEY_RIGHT:
      engine_.MovePlayer(mylibrary::Direction::kRight);
      break;
    case KeyEvent::KEY_LEFT:
      engine_.MovePlayer(mylibrary::Direction::kLeft);
      break;
  }
}

void MyApp::mouseDown( cinder::app::MouseEvent event ) {
  if (engine_.has_proper_contact_occured) {
    ReplayGame(event.getPos());
  }
  if ((event.getPos().x / 200) > engine_.GetPlayer()->player_body->GetPosition().x) {
    engine_.MovePlayer(mylibrary::Direction::kRight);
  }
  if ((event.getPos().x / 200) < engine_.GetPlayer()->player_body->GetPosition().x) {
    engine_.MovePlayer(mylibrary::Direction::kLeft);
  }
}

void MyApp::mouseDrag( cinder::app::MouseEvent event ) {
  if ((event.getPos().x / 200) > engine_.GetPlayer()->player_body->GetPosition().x) {
    engine_.MovePlayer(mylibrary::Direction::kRight);
  }
  if ((event.getPos().x / 200) < engine_.GetPlayer()->player_body->GetPosition().x) {
    engine_.MovePlayer(mylibrary::Direction::kLeft);
  }
}

void MyApp::mouseUp( cinder::app::MouseEvent event ) {}

}

// namespace myapp
