// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <cinder/Rand.h>
#include <Box2D/Box2D.h>
#include <mylibrary/engine.h>

mylibrary::Engine engine_;

TEST_CASE("Random sanity test", "[random]") {
  engine_.setup();
  engine_.AddMeteor();
  REQUIRE(engine_.count == 1);
}