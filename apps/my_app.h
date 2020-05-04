// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <Box2D/Box2D.h>
#include <cinder/gl/gl.h>
#include <mylibrary/engine.h>




namespace myapp {

class MyApp : public cinder::app::App {

  const float METERS_TO_POINTS = 100.0f;
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
  void mouseDown( cinder::app::MouseEvent event ) override;
  void mouseDrag( cinder::app::MouseEvent event ) override;
  void mouseUp( cinder::app::MouseEvent event ) override;

 private:
  void DrawMeteor(mylibrary::Meteor meteor);
  void DrawGround();
  void DrawPlayer();
  void DrawGameOver();
  void DrawReplayButton();
  void ReplayGame(cinder::vec2 position);
  mylibrary::Engine engine_;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
