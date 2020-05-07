// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"


namespace myapp {

MyApp::MyApp() = default;

void MyApp::setup() {
  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();

  engine_.Setup();

  cinder::audio::SourceFileRef sourceFile = cinder::audio::load(
      cinder::app::loadAsset(
          "Cinematic-electronic-track.mp3"));
  background_music = cinder::audio::Voice::create(sourceFile);
  background_music->start();

  cinder::audio::SourceFileRef game_over_file = cinder::audio::load(
      cinder::app::loadAsset(
          "gameover.mp3"));
  game_over_music = cinder::audio::Voice::create(game_over_file);

  engine_.GetPlayer()->SetPlayerTexture("transparent_player.png");
}

void MyApp::update() {
  engine_.Update("transparent_meteor.png");
}

void MyApp::draw() {
  cinder::gl::clear();
  cinder::gl::enableAlphaBlending();

  if (engine_.GetIsGameOver()) {
    DrawGameOver();
    DrawReplayButton();
    background_music->stop();
    return;
  }

  if (engine_.GetWave() == mylibrary::Wave::kWaveThree ||
      engine_.GetWave() == mylibrary::Wave::kWaveFour) {
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

void MyApp::DrawMeteor(const mylibrary::Meteor& meteor) {
  float meteor_radius =
      meteor.meteor_body->GetFixtureList()->GetShape()->m_radius;
  const int kMeteorRadiusScale = 2;
  cinder::vec2 meteor_vector =
      cinder::vec2(meteor.meteor_body->GetPosition().x,
                   meteor.meteor_body->GetPosition().y) *
                   (mylibrary::Conversions::kMetersToPoints /
                   kMeteorRadiusScale);

  cinder::gl::ScopedModelMatrix model_scope;
  cinder::gl::translate(meteor_vector);
  cinder::gl::color(cinder::Color::white());

  cinder::Rectf meteor_rect(
      meteor_vector.x - (meteor_radius *
      (mylibrary::Conversions::kMetersToPoints)),
      meteor_vector.y - (meteor_radius *
      (mylibrary::Conversions::kMetersToPoints)),
      meteor_vector.x + (meteor_radius *
      (mylibrary::Conversions::kMetersToPoints)),
      meteor_vector.y + (meteor_radius *
      (mylibrary::Conversions::kMetersToPoints)));

  cinder::gl::draw(meteor.GetMeteorTexture(), meteor_rect);
}

void MyApp::DrawBarrier() {
  cinder::gl::color(1, 1, 1);

  mylibrary::Barrier* barrier = engine_.GetBarrier();
  cinder::vec2 position_vector =
      cinder::vec2(barrier->barrier_body->GetPosition().x,
                   barrier->barrier_body->GetPosition().y) *
      (mylibrary::Conversions::kMetersToPoints);

  cinder::Rectf barrier_rect(position_vector.x - barrier->kBarrierWidth,
                             position_vector.y - barrier->kBarrierHeight,
                             position_vector.x + barrier->kBarrierWidth,
                             position_vector.y + barrier->kBarrierHeight);

  cinder::gl::drawSolidRect(barrier_rect);
}

void MyApp::DrawPlayer() {
  cinder::gl::color(cinder::Color::white());

  mylibrary::Player* player = engine_.GetPlayer();
  cinder::vec2 position_vector =
      cinder::vec2(player->player_body->GetPosition().x,
                   player->player_body->GetPosition().y) *
      (mylibrary::Conversions::kMetersToPoints);

  cinder::Rectf player_rect(position_vector.x - player->kPlayerRadius,
                            position_vector.y - player->kPlayerRadius,
                            position_vector.x + player->kPlayerRadius,
                            position_vector.y + player->kPlayerRadius);

  cinder::gl::draw(player->GetPlayerTexture(), player_rect);
}

void MyApp::DrawBackground() {
  cinder::gl::color(cinder::Color::white());

  cinder::gl::TextureRef background = cinder::gl::Texture::create(
      cinder::loadImage(cinder::app::loadAsset(
          "background_transparent.png")));

  cinder::Rectf background_rect(0, 0, cinder::app::getWindowWidth(),
                                cinder::app::getWindowHeight());

  cinder::gl::draw(background, background_rect);
}

void MyApp::DrawCurrentWave(const mylibrary::Wave& wave) {
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

  cinder::gl::color(0.23, 0.1, 0.89);
  const cinder::vec2 center = {50, 50};
  const cinder::ivec2 size = {100, 100};
  const cinder::Color color = cinder::Color::white();

  PrintText(current_wave, color, size, center,
      0.4, 1, 40);
}

void MyApp::DrawGameOver() {
  game_over_music->start();
  cinder::gl::clear(cinder::Color(0.3, 0.4, 0.5));
  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {500, 100};
  const cinder::Color color = cinder::Color::black();
  const std::string text = "Game Over!!";

  PrintText(text, color, size, center,
      0, 0, 80);
}

void MyApp::DrawReplayButton() {
  cinder::gl::color(0.23, 0.65, 0.09);
  cinder::vec2 center = getWindowCenter();
  center.y = center.y + 200;
  const cinder::ivec2 size = {400, 100};
  const cinder::Color color = cinder::Color::white();
  const std::string replay = "Replay Game";

  PrintText(replay, color, size, center,
      0.4, 1, 80);
}

void MyApp::PrintText(const std::string& text,
                      const cinder::Color& color,
                      const cinder::ivec2& size,
                      const cinder::vec2& loc,
                      const double color_value,
                      const double alpha_value,
                      const double font_size) {
  auto box = cinder::TextBox()
      .alignment(cinder::TextBox::CENTER)
      .font(cinder::Font("Arial", font_size))
      .size(size)
      .color(color)
      .backgroundColor(cinder::ColorA(
          0, 0, color_value, alpha_value))
      .text(text);

  const auto box_size = box.getSize();
  const cinder::vec2 locp = {loc.x - box_size.x / 2,
                             loc.y - box_size.y / 2};
  const auto surface = box.render();
  const auto texture = cinder::gl::Texture::create(surface);
  cinder::gl::draw(texture, locp);
}

void MyApp::ReplayGame(const cinder::vec2& position) {
  const int kReplayButtonRightSide = 600;
  const int kReplayButtonLeftSide = 200;
  const int kReplayButtonTopSide = 550;
  const int kReplayButtonBottomSide = 650;

  if ((position.x < kReplayButtonRightSide ||
  position.x > kReplayButtonLeftSide) &&
      (position.y < kReplayButtonTopSide ||
      position.y > kReplayButtonBottomSide)) {
    game_over_music->stop();
    engine_.Reset();
    setup();
  }
}

void MyApp::keyDown(cinder::app::KeyEvent event) {
  switch (event.getCode()) {
    case cinder::app::KeyEvent::KEY_RIGHT:
      engine_.MovePlayer(mylibrary::Direction::kRight);
      break;

    case cinder::app::KeyEvent::KEY_LEFT:
      engine_.MovePlayer(mylibrary::Direction::kLeft);
      break;
  }
}

void MyApp::mouseDown(cinder::app::MouseEvent event) {
  if (engine_.GetIsGameOver()) {
    ReplayGame(event.getPos());
  }

  if ((event.getPos().x * mylibrary::Conversions::kPointsToMeters) >
      engine_.GetPlayer()->player_body->GetPosition().x) {
    engine_.MovePlayer(mylibrary::Direction::kRight);
  }

  if ((event.getPos().x * mylibrary::Conversions::kPointsToMeters) <
      engine_.GetPlayer()->player_body->GetPosition().x) {
    engine_.MovePlayer(mylibrary::Direction::kLeft);
  }
}

void MyApp::mouseDrag(cinder::app::MouseEvent event) {
  if ((event.getPos().x * mylibrary::Conversions::kPointsToMeters) >
      engine_.GetPlayer()->player_body->GetPosition().x) {
    engine_.MovePlayer(mylibrary::Direction::kRight);
  }

  if ((event.getPos().x * mylibrary::Conversions::kPointsToMeters) <
      engine_.GetPlayer()->player_body->GetPosition().x) {
    engine_.MovePlayer(mylibrary::Direction::kLeft);
  }
}

// namespace myapp
}