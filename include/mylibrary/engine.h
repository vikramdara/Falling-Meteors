//
// Created by vikra on 4/28/2020.
//

#ifndef FINALPROJECT_MYLIBRARY_ENGINE_H
#define FINALPROJECT_MYLIBRARY_ENGINE_H

#include <Box2D/Box2D.h>
#include <cinder/Rand.h>
#include <cinder/Timer.h>
#include <mylibrary/Conversion.h>
#include <mylibrary/Direction.h>
#include <mylibrary/Level.h>
#include <mylibrary/Meteor.h>
#include <mylibrary/Player.h>
#include <cinder/app/AppBase.h>

namespace mylibrary {

class Engine : public b2ContactListener {

 public:
  void setup();
  void CreateGround();
  void reset();
  void AddMeteor();
  b2World* GetWorld();
  void update();
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
