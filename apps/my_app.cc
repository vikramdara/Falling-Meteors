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
}

void MyApp::update() {
  engine_.setup();
  engine_.AddMeteor();
  float timeStep = 1.0f / 60.f;
  int32 velocityIterations = 8;
  int32 positionIterations = 3;
  world_->Step(timeStep, velocityIterations, positionIterations);
  count = 0;
  if (count == 2000) {
    engine_.reset();
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
  mylibrary::Meteor meteor = engine_.GetMeteor(0);
  b2Body* meteor_body = meteor.GetMeteorBody();
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
