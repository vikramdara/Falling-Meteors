// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <cinder/Rand.h>
#include <Box2D/Box2D.h>
#include <mylibrary/engine.h>


TEST_CASE("New Player", "[CreatePlayer]") {

}

TEST_CASE("New hi", "[CreatePlayer]") {
  mylibrary::Engine engine_;
  engine_.setup();
  REQUIRE(engine_.GetPlayer()->density == 2.0f);
  engine_.reset();
}