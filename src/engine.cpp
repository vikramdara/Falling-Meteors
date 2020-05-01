//
// Created by vikra on 4/28/2020.
//

#include <mylibrary/engine.h>

#include <memory>

namespace mylibrary {

void Engine::setup() {
  b2Vec2 gravity(0, 10);
  world_ = new b2World(gravity);
  CreateGround();
  CreatePlayer();
  timer.start();
}


void Engine::CreateGround() {
  b2BodyDef groundBodyDef;
  groundBodyDef.type = b2_staticBody;
  groundBodyDef.position.Set(pointsToMeters(cinder::app::getWindowWidth() / 2), pointsToMeters(cinder::app::getWindowHeight() - 50));
  groundBody_ = world_->CreateBody(&groundBodyDef);

  b2PolygonShape groundBox;
  groundBox.SetAsBox(pointsToMeters(cinder::app::getWindowWidth() / 2),pointsToMeters(50));
  groundBody_->CreateFixture(&groundBox, 1.0f);
}

void Engine::CreatePlayer() {
  b2BodyDef user_body;
  user_body.type = b2_staticBody;
  user_body.position.Set(pointsToMeters(cinder::app::getWindowWidth() / 2), pointsToMeters(cinder::app::getWindowHeight() - 125));
  player.player_body = world_->CreateBody(&user_body);

  b2PolygonShape player_center;
  player_center.SetAsBox(pointsToMeters(25), pointsToMeters(25));
  player.player_body->CreateFixture(&player_center, 1.0f);
}


ci::vec2 Engine::ToCinder( const b2Vec2 &vec ) {
  return cinder::vec2( vec.x, vec.y );
}
ci::Color Engine::ToCinder( const b2Color &color ) {
  return cinder::Color( color.r, color.g, color.b );
}

void Engine::reset() {
  meteors.clear();
}

void Engine::AddMeteor() {
  cinder::vec2 pos = cinder::vec2(cinder::randFloat(0, cinder::app::getWindowWidth()), cinder::randFloat( -40, -100));
  cinder::vec2 posScaled = pointsToMeters( pos );
  Meteor new_meteor;
  b2BodyDef meteor;
  meteor.type = b2_dynamicBody;
  //meteor.allowSleep = false;
  meteor.position.Set(posScaled.x, posScaled.y);
  new_meteor.meteor_body = world_->CreateBody(&meteor);

  b2CircleShape shape;
  shape.m_radius = 0.2f;

  b2FixtureDef fixtureDef;
  fixtureDef.shape = &shape;
  fixtureDef.density = 1.0f;
  fixtureDef.friction = 1.0f;
  fixtureDef.restitution = 0.4f;

  new_meteor.meteor_body->CreateFixture(&fixtureDef);
  meteors.push_back(new_meteor);
  count++;
}

Engine::Meteor Engine::GetMeteor(int index) {
  return meteors[index];
}

Engine::Player Engine::GetPlayer() {
  return player;
}

void Engine::MovePlayer(Direction direction) {
  switch (direction) {
    case Direction::kRight:
      player.player_body->SetTransform(b2Vec2(player.player_body->GetPosition().x + 0.125, player.player_body->GetPosition().y), 0);
      break;
    case Direction::kLeft:
      player.player_body->SetTransform(b2Vec2(player.player_body->GetPosition().x - 0.125, player.player_body->GetPosition().y), 0);
      break;
  }
}

b2World* Engine::GetWorld() {
  return world_;
}

void Engine::update() {
  float timeStep = 1.0f / 60.0f;
  int32 velocityIterations = 8;
  int32 positionIterations = 3;
  world_->Step(timeStep, velocityIterations, positionIterations);
  size_t time_counter = 2;
  if (timer.getSeconds() >= time_counter) {
    AddMeteor();
    timer.stop();
    timer.start();
  }

}


}