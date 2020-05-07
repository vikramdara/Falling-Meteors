//
// Created by vikra on 5/6/2020.
//

#include "mylibrary/Barrier.h"
#include <cinder/Rand.h>

namespace mylibrary {

Barrier::Barrier(b2World* world) {
  cinder::randSeed(std::time(nullptr));

  const float kBarrierHeightUpperBound = 550;
  const float kBarrierHeightLowerBound = 650;

  cinder::vec2 pos = cinder::vec2(
      cinder::randFloat(
          kBarrierWidth, cinder::app::getWindowWidth() - kBarrierWidth),
          cinder::randFloat(
              kBarrierHeightUpperBound, kBarrierHeightLowerBound));
  cinder::vec2 posScaled = mylibrary::Conversions::PointsToMeters(pos);

  b2BodyDef barrier_body_def;
  barrier_body_def.type = b2_staticBody;
  barrier_body_def.position.Set(posScaled.x, posScaled.y);
  barrier_body = world->CreateBody(&barrier_body_def);

  b2PolygonShape barrier_box;
  barrier_box.SetAsBox(mylibrary::Conversions::PointsToMeters(kBarrierWidth),
                       mylibrary::Conversions::PointsToMeters(kBarrierHeight));
  barrier_body->CreateFixture(&barrier_box, 1.0f);
}

Barrier::~Barrier() = default;

}
