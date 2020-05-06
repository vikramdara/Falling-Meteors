//
// Created by vikra on 5/6/2020.
//

#include "mylibrary/Barrier.h"
#include <cinder/Rand.h>

namespace mylibrary {

Barrier::Barrier(b2World* world) {
  cinder::randSeed(std::time(nullptr));
  cinder::vec2 pos = cinder::vec2(cinder::randFloat(75, cinder::app::getWindowWidth() - 75), cinder::randFloat( 550, 650));
  cinder::vec2 posScaled = mylibrary::Conversions::pointsToMeters( pos );
  b2BodyDef barrier_body_def;
  barrier_body_def.type = b2_staticBody;
  barrier_body_def.position.Set(posScaled.x, posScaled.y);
  barrier_body = world->CreateBody(&barrier_body_def);

  b2PolygonShape barrier_box;
  barrier_box.SetAsBox(mylibrary::Conversions::pointsToMeters(75),mylibrary::Conversions::pointsToMeters(15));
  barrier_body->CreateFixture(&barrier_box, 1.0f);


  /**

void Engine::CreateGround() {
  b2BodyDef groundBodyDef;
  groundBodyDef.type = b2_staticBody;
  groundBodyDef.position.Set(pointsToMeters(cinder::app::getWindowWidth() / 2), pointsToMeters(cinder::app::getWindowHeight() - 50));
  groundBody_ = world_->CreateBody(&groundBodyDef);

  b2PolygonShape groundBox;
  groundBox.SetAsBox(pointsToMeters(cinder::app::getWindowWidth() / 2),pointsToMeters(50));
  groundBody_->CreateFixture(&groundBox, 1.0f);
}

 */
}

}
