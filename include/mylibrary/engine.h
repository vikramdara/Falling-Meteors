//
// Created by vikra on 4/28/2020.
//

#ifndef FINALPROJECT_MYLIBRARY_ENGINE_H
#define FINALPROJECT_MYLIBRARY_ENGINE_H

#include <Box2D/Box2D.h>
#include <cinder/app/App.h>
#include <mylibrary/meteor.h>


const float METERS_TO_POINTS = 200.0f;
const float POINTS_TO_METERS = 0.005f;

namespace mylibrary {

class Engine {

 public:
  void setup();
  void CreateGround();
  void reset();
  void AddMeteor(const ci::vec2 &pos );
  Meteor GetMeteor(int index);
  b2World* GetWorld();
  void update();
  b2Body* groundBody_;
  int count = 0;
  float metersToPoints( float var )			{ return var * METERS_TO_POINTS; }
  cinder::vec2 metersToPoints( const cinder::vec2 &var )	{ return var * METERS_TO_POINTS; }
  float pointsToMeters( float var )			{ return var * POINTS_TO_METERS; }
  cinder::vec2 pointsToMeters( const cinder::vec2 &var )	{ return var * POINTS_TO_METERS; }
  b2Vec2 pointsToMeters( const b2Vec2 &var )	{ return POINTS_TO_METERS * var; }


 private:
  b2World* world_;
  std::vector<Meteor> meteors;

  ci::vec2 ToCinder( const b2Vec2 &vec );
  ci::Color ToCinder( const b2Color &color );

};

}

#endif  // FINALPROJECT_MYLIBRARY_ENGINE_H
