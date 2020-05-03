//
// Created by vikra on 4/28/2020.
//

#include <mylibrary/engine.h>

#include <memory>

namespace mylibrary {

void Engine::setup() {
  b2Vec2 gravity(0, 10);
  world_ = new b2World(gravity);
  world_->SetContactListener(this);
  CreateGround();
  CreatePlayer();
  timer.start();
}


void Engine::CreateGround() {
  b2BodyDef groundBodyDef;
  groundBodyDef.type = b2_staticBody;
  groundBodyDef.position.Set(pointsToMeters(cinder::app::getWindowWidth() / 2), pointsToMeters(cinder::app::getWindowHeight() - 50));
  groundBody_ = world_->CreateBody(&groundBodyDef);

  b2PolygonShape groundBox;
  groundBox.SetAsBox(pointsToMeters(cinder::app::getWindowWidth() / 2),pointsToMeters(50));
  groundBody_->CreateFixture(&groundBox, 1.0f);
}

void Engine::CreatePlayer() {
  player = new mylibrary::Player(world_);
}

void Engine::reset() {
  delete world_;
  meteors.clear();
}

void Engine::AddMeteor() {
  meteors.emplace_back(world_, 0.2f);
  count++;
}

Meteor Engine::GetMeteor(int index) {
  return meteors[index];
}

mylibrary::Player* Engine::GetPlayer() {
  return player;
}

void Engine::MovePlayer(Direction direction) {
  switch (direction) {
    case Direction::kRight:
      player->player_body->SetTransform(b2Vec2(player->player_body->GetPosition().x + 0.125, player->player_body->GetPosition().y), 0);
      break;
    case Direction::kLeft:
      player->player_body->SetTransform(b2Vec2(player->player_body->GetPosition().x - 0.125, player->player_body->GetPosition().y), 0);
      break;
  }
}

b2World* Engine::GetWorld() {
  return world_;
}

void Engine::update() {
  float timeStep = 1.0f / 60.0f;
  int32 velocityIterations = 8;
  int32 positionIterations = 3;
  world_->Step(timeStep, velocityIterations, positionIterations);
  size_t time_counter = 1;
  if (timer.getSeconds() >= time_counter) {
    AddMeteor();
    timer.stop();
    timer.start();
  }
  RemoveOffScreenMeteors();

}

void Engine::BeginContact( b2Contact* contact ) {
  void* body_one = contact->GetFixtureA()->GetBody()->GetUserData();
  void* body_two = contact->GetFixtureB()->GetBody()->GetUserData();

  if (body_one == nullptr || body_two == nullptr) {
    return;
  }

  if (contact->GetFixtureA()->GetDensity() == 2.0f
  || contact->GetFixtureB()->GetDensity() == 2.0f) {
    has_proper_contact_occured = true;
  }
}

void Engine::RemoveOffScreenMeteors() {
  float window_height_meters = pointsToMeters(cinder::app::getWindowHeight());
  float window_width_meters = pointsToMeters(cinder::app::getWindowWidth());

  b2Body* node = world_->GetBodyList();
  while (node)
  {
    b2Body* b = node;
    node = node->GetNext();
    if (b->GetType() == b2_dynamicBody) {
      //Meteor* meteor = (Meteor*)b->GetUserData();
      //b2Body* c = meteor->meteor_body;
      if (b->GetPosition().x > window_width_meters
          || b->GetPosition().x < 0) {
        world_->DestroyBody(b);
      }
    }
  }


  meteors.erase(
      std::remove_if(
          meteors.begin(),
          meteors.end(),
          [window_width_meters](Meteor const & meteor) {
            return meteor.meteor_body->GetPosition().x > window_width_meters
            || meteor.meteor_body->GetPosition().x < 0;
          }
      ),
      meteors.end()
  );


  count = world_->GetBodyCount() - 2;
  /**
  for (Meteor* meteor : meteors) {
    if (meteor->meteor_body->GetPosition().x > window_width_meters ||
    meteor->meteor_body->GetPosition().x < 0) {
      world_->DestroyBody(meteor->meteor_body);
      delete meteor;
    }
  }

   */

}

}  // namespace mylibrary