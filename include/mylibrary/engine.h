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

  /**
   * Setup method intialized necessary global variables and sets contact
   * listener to detect collisions.
   */
  void Setup();

  /**
   * Reset method resets all global variables, essentially restarting the game
   */
  void Reset();

  /**
   * Update method updates the game by 1/60 of a second
   */
  void Update(const std::string& meteor_texture);

  /**
   * MovePlayer method moves the player in a direction. Won't do anything if the
   * player is trying to move offscreen.
   * @param direction is the direction the player will move
   */

  /**
   * This method sets the current wave depending on how much time has passed
   */
  void SetWave(int seconds_passed);

  void MovePlayer(const Direction& direction);

  /**
   * These next 5 methods all return the private global variables
   */
  std::vector<Meteor> GetMeteors();
  mylibrary::Player* GetPlayer();
  mylibrary::Barrier* GetBarrier();
  mylibrary::Wave GetWave();
  b2World* GetWorld() const;
  bool GetIsGameOver();
  double GetRateOfMeteorDrops() const;
  bool GetIsBarrierMade() const;

 private:

  /**
   * This method adds a meteor to the game
   * @param wave is the current wave we are in used to determine the starting
   * position of the meteor
   */
  void AddMeteor(const mylibrary::Wave& wave, const std::string& meteor_texture);

  /**
   * This is an overloaded box2d method for handling collisions. If a player
   * and meteor collide the game is over, if not nothing happens.
   * @param contact
   */
  void BeginContact(b2Contact* contact) override;

  /**
   * This method creates a new player object
   */
  void CreatePlayer();

  /**
   * This method creates a new barrier if game is on the correct wave
   */
  void CreateBarrier();

  /**
   * This method gets rid of the meteors that have gone offscreen. Destroys all
   * necessary bodies.
   */
  void RemoveOffScreenMeteors();

  /**
   * This method checks to see if the player is on the edge of the screen and
   * player is trying to move in the direction that put it offscreen
   * @param direction Is the direction the player is trying to go to
   * @return if the player is trying to go out of the screen
   */
  bool IsPlayerOnScreenEdge(const Direction& direction);

  /**
   * This is the world in which all mechanics and physics takes place.
   */
  b2World* world_;

 private:
  /**
   * This is the player of the game.
   */
  mylibrary::Player* player;

  /**
   * This is the support barrier that arises on wave 3 and 4.
   */
  mylibrary::Barrier* barrier;

  /**
   * This is a list of meteors that are currently on the screen.
   */
  std::vector<Meteor> meteors;

  /**
   * This is a timer that is used to keep track of when meteors should be added
   */
  cinder::Timer meteor_timer;

  /**
   * This is a timer that is used to see when the wave needs to change
   */
  cinder::Timer wave_timer;

  /**
   * This is a time that is used in wave four to see when the meteor starting
   * position needs to change
   */
  cinder::Timer wave_four_timer;

  /**
   * This is the current wave that the player is in. Default to wave one.
   */
  mylibrary::Wave current_wave;

  /**
   * This is the variable used to determine the rate in which meteors fall
   */
  double rate_of_meteor_drops;

  /**
   * Boolean to see if a barrier is already made. Used to stop making multiple
   * barriers.
   */
  bool is_barrier_made;

 private:
  /**
   * Boolean to see if the wave four timer has started. Used to make sure the
   * timer doesn't reset in every single class
   */
  bool has_wave_four_timer_started;

  /**
   * Boolean to see if the game is over. Set to true upon a
   * collision or if player survives the four waves.
   */
  bool is_game_over = false;
};

}

#endif  // FINALPROJECT_MYLIBRARY_ENGINE_H
