//
// Created by vikra on 4/28/2020.
//

#ifndef FINALPROJECT_MYLIBRARY_ENGINE_H
#define FINALPROJECT_MYLIBRARY_ENGINE_H

#include <Box2D/Box2D.h>
#include <cinder/Rand.h>
#include <cinder/app/App.h>
#include <mylibrary/Meteor.h>
#include <mylibrary/Player.h>

const float METERS_TO_POINTS = 200.0f;
const float POINTS_TO_METERS = 0.005f;

namespace mylibrary {

enum class Direction {kLeft, kRight};

class Engine : public b2ContactListener {

 public:
  void setup();
  void CreateGround();
  void reset();
  void AddMeteor();
  b2World* GetWorld();
  void update();
  float metersToPoints( float var )			{ return var * METERS_TO_POINTS; }
  cinder::vec2 metersToPoints( const cinder::vec2 &var )	{ return var * METERS_TO_POINTS; }
  float pointsToMeters( float var )			{ return var * POINTS_TO_METERS; }
  cinder::vec2 pointsToMeters( const cinder::vec2 &var )	{ return var * POINTS_TO_METERS; }
  b2Vec2 pointsToMeters( const b2Vec2 &var )	{ return POINTS_TO_METERS * var; }
  void BeginContact( b2Contact* contact ) override;
  bool has_proper_contact_occured = false;
  void CreatePlayer();
  void MovePlayer(Direction direction);
  std::vector<Meteor> GetMeteors();
  mylibrary::Player* GetPlayer();
  void RemoveOffScreenMeteors();


 private:
  b2World* world_;
  std::vector<Meteor> meteors;
  cinder::Timer timer;
  mylibrary::Player* player;
  //b2Body* groundBody_;

};

}

#endif  // FINALPROJECT_MYLIBRARY_ENGINE_H
