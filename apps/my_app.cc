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
  DrawGround();
  for (int x = 0; x < engine_.count; x++) {
    DrawMeteor(engine_.GetMeteor(x));
  }
}

void MyApp::DrawMeteor(mylibrary::Meteor meteor) {
  float t = meteor.meteor_body->GetAngle();
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
  cinder::Rectf wall_rect(0,
                          cinder::app::getWindowHeight() - 100,
                          cinder::app::getWindowWidth() + 0,
                          cinder::app::getWindowHeight() + 0);
  cinder::gl::drawSolidRect(wall_rect);
}

void MyApp::keyDown(KeyEvent event) { }

void MyApp::mouseDown( cinder::app::MouseEvent event )
{
  engine_.AddMeteor( event.getPos() );
}

void MyApp::mouseDrag( cinder::app::MouseEvent event )
{
  engine_.AddMeteor( event.getPos() );
}

void MyApp::mouseUp( cinder::app::MouseEvent event )
{
}

}

// namespace myapp
