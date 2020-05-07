// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <Box2D/Box2D.h>
#include <mylibrary/engine.h>

mylibrary::Engine engine_;

TEST_CASE("Correct Gravity", "[Setup]") {
  engine_.Setup();
  b2Vec2 correct_gravity(0, 10);
  REQUIRE(correct_gravity == engine_.GetWorld()->GetGravity());
  engine_.Reset();
}

TEST_CASE("Correct Initial Wave", "[Setup]") {
  engine_.Setup();
  REQUIRE(mylibrary::Wave::kWaveOne == engine_.GetWave());
  engine_.Reset();
}

TEST_CASE("Wave One Mechanics", "[SetWave]") {
  engine_.Setup();
  engine_.Update("transparent_meteor.png");
  REQUIRE(engine_.GetRateOfMeteorDrops() == 1);
  engine_.Reset();
}

TEST_CASE("Wave Two Mechanics", "[SetWave]") {
  engine_.Setup();
  engine_.SetWave(17);
  REQUIRE(engine_.GetRateOfMeteorDrops() == 0.7);
  REQUIRE(engine_.GetWave() == mylibrary::Wave::kWaveTwo);
  engine_.Reset();
}

TEST_CASE("Wave Three Mechanics", "[SetWave]") {
  engine_.Setup();
  engine_.SetWave(31);
  REQUIRE(engine_.GetRateOfMeteorDrops() == 0.4);
  REQUIRE(engine_.GetWave() == mylibrary::Wave::kWaveThree);
  REQUIRE(engine_.GetIsBarrierMade());
  engine_.Reset();
}

TEST_CASE("Wave Four Mechanics", "[SetWave]") {
  engine_.Setup();
  engine_.SetWave(46);
  REQUIRE(engine_.GetRateOfMeteorDrops() == 0.2);
  REQUIRE(engine_.GetWave() == mylibrary::Wave::kWaveFour);
  engine_.Reset();
}

TEST_CASE("Default Mechanics", "[SetWave]") {
  engine_.Setup();
  engine_.SetWave(61);
  REQUIRE(engine_.GetIsGameOver());
  engine_.Reset();
}

TEST_CASE("Move Player Mechanics", "[MovePlayer]") {
  engine_.Setup();
  b2Vec2 initial_position = engine_.GetPlayer()->player_body->GetPosition();
  engine_.MovePlayer(mylibrary::Direction::kLeft);
  b2Vec2 new_position = engine_.GetPlayer()->player_body->GetPosition();
  REQUIRE(!(initial_position == new_position));
  engine_.Reset();
}