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

  b2Vec2 gravity(0.0f, 10.0f);
  world_ = new b2World(gravity);

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

void MyApp::update() {
  float timeStep = 1.0f / 60.f;
  int32 velocityIterations = 8;
  int32 positionIterations = 3;
  world_->Step(timeStep, velocityIterations, positionIterations);
  count = 0;
  if (count == 2000) {
    delete world_;
  }
  count++;

}

void MyApp::draw() {
  cinder::gl::clear();
  cinder::gl::color(1,1,0);
  cinder::Rectf wall_rect( 0, cinder::app::getWindowHeight() - 100, cinder::app::getWindowWidth(), cinder::app::getWindowHeight());
  cinder::gl::drawSolidRect(wall_rect);
  DrawMeteor();
}

void MyApp::DrawMeteor() {
  b2BodyDef meteor;
  meteor.type = b2_dynamicBody;
  meteor.allowSleep = false;
  meteor.position.Set( 2, 0 );

  const float velMax = 5;
  meteor.linearVelocity = b2Vec2( cinder::Rand::randFloat( -velMax, velMax ), cinder::Rand::randFloat( -velMax, 0 ) );

  b2CircleShape shape;
  shape.m_radius = 1.0f;

  b2FixtureDef fixtureDef;
  fixtureDef.shape = &shape;
  fixtureDef.density = 1.0f;
  fixtureDef.friction = 1.0f;
  fixtureDef.restitution = 0.4f;
  b2Body* meteor_body = world_->CreateBody(&meteor);
  meteor_body->CreateFixture(&fixtureDef);
  float t = meteor_body->GetAngle();
  cinder::vec2 position_vector = cinder::vec2(meteor_body->GetPosition().x, meteor_body->GetPosition().y) * METERS_TO_POINTS;
  cinder::gl::ScopedModelMatrix modelScope;
  cinder::gl::translate(position_vector);
  cinder::gl::rotate( t );
  cinder::gl::color(1,0,0);
  cinder::gl::drawSolidCircle(position_vector, 20.0f, 20);

}

void MyApp::keyDown(KeyEvent event) { }


ci::vec2 MyApp::ToCinder( const b2Vec2 &vec ) {
  return cinder::vec2( vec.x, vec.y );
}
ci::Color MyApp::ToCinder( const b2Color &color ) {
  return cinder::Color( color.r, color.g, color.b );
}

}

// namespace myapp
