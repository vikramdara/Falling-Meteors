// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>



namespace myapp {

using cinder::app::KeyEvent;

MyApp::MyApp() { }

void MyApp::setup() {
  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();

  b2Vec2 gravity(0.0f, -10.0f);
  b2World world_(gravity);
  b2BodyDef groundBodyDef;
  groundBodyDef.position.Set(340.0f, 340.0f);
  groundBody = world_.CreateBody(&groundBodyDef);
  b2PolygonShape groundBox;
  groundBox.SetAsBox(50.0f, 10.0f);
  groundBody->CreateFixture(&groundBox, 0.0f);
}

void MyApp::update() {

}

void MyApp::draw() {
  cinder::gl::enableAlphaBlending();
  cinder::gl::clear();
  cinder::gl::color(1,1,0);
  cinder::gl::drawSolidCircle( toCinder(groundBody->GetPosition()) , 90, 20 );
}

void MyApp::keyDown(KeyEvent event) { }


ci::vec2 MyApp::toCinder( const b2Vec2 &vec ) {
  return cinder::vec2( vec.x, vec.y );
}
ci::Color MyApp::toCinder( const b2Color &color ) {
  return cinder::Color( color.r, color.g, color.b );
}

}

// namespace myapp
