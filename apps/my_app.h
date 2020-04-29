// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <Box2D/Box2D.h>
#include <cinder/gl/gl.h>
#include <mylibrary/meteor.h>
#include <mylibrary/engine.h>




namespace myapp {

class MyApp : public cinder::app::App {

  const float METERS_TO_POINTS = 100;
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;

 private:
  ci::vec2 ToCinder( const b2Vec2 &vec );
  ci::Color ToCinder( const b2Color &color );
  void DrawMeteor();


  std::vector<cinder::vec2> vertices;
  b2World* world_;
  b2Body* groundBody_;
  int count = 0;
  mylibrary::Engine engine_;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
