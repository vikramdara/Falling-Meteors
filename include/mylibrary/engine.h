//
// Created by vikra on 4/28/2020.
//

#ifndef FINALPROJECT_MYLIBRARY_ENGINE_H
#define FINALPROJECT_MYLIBRARY_ENGINE_H

#include <Box2D/Box2D.h>
#include <cinder/app/App.h>
#include <mylibrary/meteor.h>



namespace mylibrary {

class Engine {

 public:
  void setup();
  void CreateGround();
  void reset();
  void AddMeteor();
  Meteor GetMeteor(int index);


 private:
  b2World* world_;
  std::vector<cinder::vec2> vertices;
  std::vector<Meteor> meteors;

  ci::vec2 GetVertices(int index);
  ci::vec2 ToCinder( const b2Vec2 &vec );
  ci::Color ToCinder( const b2Color &color );

};

}

#endif  // FINALPROJECT_MYLIBRARY_ENGINE_H
