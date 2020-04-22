// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <Box2D/Box2D.h>
#include <cinder/gl/gl.h>



namespace myapp {

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;

 private:
  ci::vec2 toCinder( const b2Vec2 &vec );
  ci::Color toCinder( const b2Color &color );


  b2Body* groundBody;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
