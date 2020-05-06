//
// Created by vikra on 4/28/2020.
//

#ifndef FINALPROJECT_MYLIBRARY_ENGINE_H
#define FINALPROJECT_MYLIBRARY_ENGINE_H

#include <Box2D/Box2D.h>
#include <cinder/Rand.h>
#include <cinder/Timer.h>
#include <cinder/app/AppBase.h>
#include <mylibrary/Conversion.h>
#include <mylibrary/Direction.h>
#include <mylibrary/Wave.h>
#include <mylibrary/Meteor.h>
#include <mylibrary/Player.h>

#include "Barrier.h"

namespace mylibrary {

class Engine : public b2ContactListener {

 public:
  void setup();
  void CreateGround();
  void reset();
  void AddMeteor(mylibrary::Wave wave);
  b2World* GetWorld();
  void update();
  void BeginContact( b2Contact* contact ) override;
  bool is_game_over = false;
  void CreatePlayer();
  void CreateBarrier();
  void MovePlayer(Direction direction);
  std::vector<Meteor> GetMeteors();
  mylibrary::Player* GetPlayer();
  mylibrary::Barrier* GetBarrier();
  void RemoveOffScreenMeteors();
  void SetWave();
  mylibrary::Wave GetWave();
  bool IsPlayerOnScreenEdge(Direction direction);


 private:
  b2World* world_;
  std::vector<Meteor> meteors;
  cinder::Timer meteor_timer;
  cinder::Timer wave_timer;
  cinder::Timer wave_four_timer;
  mylibrary::Player* player;
  mylibrary::Barrier* barrier;
  mylibrary::Wave current_wave = mylibrary::Wave::kWaveOne;
  double time_counter;
  bool is_barrier_made;
  bool has_wave_four_timer_started;

};

}

#endif  // FINALPROJECT_MYLIBRARY_ENGINE_H
