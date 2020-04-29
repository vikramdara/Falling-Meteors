//
// Created by vikra on 4/28/2020.
//

#include <mylibrary/engine.h>

namespace mylibrary {

void Engine::setup() {
  b2Vec2 gravity(0, 10);
  world_ = new b2World(gravity);
  CreateGround();
}
void Engine::CreateGround() {
  b2Body* groundBody_;

  b2BodyDef groundBodyDef;
  groundBodyDef.type = b2_staticBody;
  groundBodyDef.position.Set(5.0f, 5.0f);
  groundBody_ = world_->CreateBody(&groundBodyDef);
  b2PolygonShape groundBox;
  //this is clockwise rn change it to counter clockwise
  vertices.emplace_back(0,cinder::app::getWindowHeight() - 100);
  vertices.emplace_back(cinder::app::getWindowWidth(), cinder::app::getWindowHeight() - 100);
  vertices.emplace_back(cinder::app::getWindowWidth(), cinder::app::getWindowHeight());
  vertices.emplace_back(0,cinder::app::getWindowHeight());
  vertices.emplace_back(0,cinder::app::getWindowHeight() - 100);

  std::vector<b2Vec2> vertsBox2d;

  for( size_t i = 0; i < vertices.size() - 1; i++ ) {
    vertsBox2d.emplace_back((vertices[i].x) / 100, (vertices[i].y) / 100);
  }
  groundBox.Set(vertsBox2d.data(), vertsBox2d.size());
  groundBody_->CreateFixture(&groundBox, 0.0f);
}

ci::vec2 Engine::ToCinder( const b2Vec2 &vec ) {
  return cinder::vec2( vec.x, vec.y );
}
ci::Color Engine::ToCinder( const b2Color &color ) {
  return cinder::Color( color.r, color.g, color.b );
}

void Engine::reset() {
  delete world_;
}

ci::vec2 Engine::GetVertices(int index) {
  if (index < 0 || index >= vertices.size()) {
    throw std::exception("Bad index");
  }
  return vertices[index];
}

void Engine::AddMeteor() {
  Meteor meteor(world_);
  meteors.push_back(std::move(meteor));
}

Meteor Engine::GetMeteor(int index) {
  return meteors[index];
}

}