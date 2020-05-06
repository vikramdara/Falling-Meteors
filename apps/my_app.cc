// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"


namespace myapp {

using cinder::app::KeyEvent;

MyApp::MyApp() {
}

void MyApp::setup() {
  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();
  engine_.setup();
  cinder::audio::SourceFileRef sourceFile = cinder::audio::load(cinder::app::loadAsset( "Cinematic-electronic-track.mp3" ));
  background_music = cinder::audio::Voice::create(sourceFile);
  background_music->start();
  cinder::audio::SourceFileRef game_over_file = cinder::audio::load(cinder::app::loadAsset( "gameover.mp3" ));
  game_over_music = cinder::audio::Voice::create(game_over_file);

}

void MyApp::update() {
  engine_.update();
}

void MyApp::draw() {
  cinder::gl::clear();
  cinder::gl::enableAlphaBlending();
  if (engine_.is_game_over) {
    DrawGameOver();
    DrawReplayButton();
    background_music->stop();
    return;
  }
  if (engine_.GetWave() == mylibrary::Wave::kWaveThree
  || engine_.GetWave() == mylibrary::Wave::kWaveFour) {
    DrawBarrier();
  }
  cinder::gl::pushMatrices();

  for (int x = 0; x < engine_.GetMeteors().size(); x++) {
    DrawMeteor(engine_.GetMeteors()[x]);
  }

  DrawPlayer();
  DrawCurrentWave(engine_.GetWave());
  DrawBackground();
  cinder::gl::popMatrices();
}

void MyApp::DrawMeteor(mylibrary::Meteor &meteor) {
  float meteor_radius = meteor.meteor_body->GetFixtureList()->GetShape()->m_radius;
  cinder::vec2 position_vector = cinder::vec2(meteor.meteor_body->GetPosition().x,
      meteor.meteor_body->GetPosition().y) *
      kMetersToPointsApp;
  cinder::gl::ScopedModelMatrix modelScope;
  cinder::gl::translate(position_vector);
  cinder::gl::color(cinder::Color::white());
  cinder::Rectf meteor_rect(position_vector.x - (meteor_radius * (kMetersToPointsApp * 2)),
                            position_vector.y - (meteor_radius * (kMetersToPointsApp * 2)),
                            position_vector.x + (meteor_radius * (kMetersToPointsApp * 2)),
                            position_vector.y + (meteor_radius * (kMetersToPointsApp * 2)));
  cinder::gl::draw(meteor.meteor_texture, meteor_rect);
}

void MyApp::DrawBarrier() {
  cinder::gl::color(1,1,1);
  mylibrary::Barrier* barrier = engine_.GetBarrier();
  cinder::vec2 position_vector = cinder::vec2(barrier->barrier_body->GetPosition().x, barrier->barrier_body->GetPosition().y) * (kMetersToPointsApp * 2);
  cinder::Rectf barrier_rect(position_vector.x - 75,
                            position_vector.y - 15,
                            position_vector.x + 75,
                            position_vector.y + 15);
  cinder::gl::drawSolidRect(barrier_rect);
}

void MyApp::DrawPlayer() {
  cinder::gl::color(cinder::Color::white());
  mylibrary::Player* player = engine_.GetPlayer();
  cinder::vec2 position_vector = cinder::vec2(player->player_body->GetPosition().x, player->player_body->GetPosition().y) * (kMetersToPointsApp * 2);
  cinder::Rectf player_rect(position_vector.x - 25,
      position_vector.y - 25,
      position_vector.x + 25,
      position_vector.y + 25);
  cinder::gl::draw(player->player_texture, player_rect);
}

void MyApp::DrawBackground() {
  cinder::gl::color(cinder::Color::white());
  cinder::gl::TextureRef background = cinder::gl::Texture::create(cinder::loadImage(cinder::app::loadAsset("background_transparent.png")));
  cinder::Rectf background_rect(0, 0, cinder::app::getWindowWidth(), cinder::app::getWindowHeight());
  cinder::gl::draw(background, background_rect);
}

void MyApp::DrawCurrentWave(mylibrary::Wave wave) {
  std::string current_wave;
  switch (wave) {
    case (mylibrary::Wave::kWaveOne):
      current_wave = "Wave one";
      break;
    case (mylibrary::Wave::kWaveTwo):
      current_wave = "Wave two";
      break;
    case (mylibrary::Wave::kWaveThree):
      current_wave = "Wave three";
      break;
    case (mylibrary::Wave::kWaveFour):
      current_wave = "Wave four";
      break;
  }

  cinder::gl::color(0.23,0.1,0.89);
  const cinder::vec2 center = {50, 50};
  const cinder::ivec2 size = {100, 100};
  const cinder::Color color = cinder::Color::white();

  auto box = cinder::TextBox()
      .alignment(cinder::TextBox::LEFT)
      .font(cinder::Font("Arial", 40))
      .size(size)
      .color(color)
      .backgroundColor(cinder::ColorA(0, 0.23, 0, 1))
      .text(current_wave);

  const auto box_size = box.getSize();
  const cinder::vec2 locp = {center.x - box_size.x / 2, center.y - box_size.y / 2};
  const auto surface = box.render();
  const auto texture = cinder::gl::Texture::create(surface);
  cinder::gl::draw(texture, locp);


}

void MyApp::DrawGameOver() {
  game_over_music->start();
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
  cinder::gl::color(0.23,0.65,0.09);
  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {400, 100};
  const cinder::Color color = cinder::Color::black();

  auto box = cinder::TextBox()
      .alignment(cinder::TextBox::CENTER)
      .font(cinder::Font("Arial", 80))
      .size(size)
      .color(color)
      .backgroundColor(cinder::ColorA(1, 0, 0, 1))
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
    game_over_music->stop();
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
  if (engine_.is_game_over) {
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
