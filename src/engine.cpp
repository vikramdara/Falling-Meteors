//
// Created by vikra on 4/28/2020.
//

#include <mylibrary/engine.h>

namespace mylibrary {

void Engine::setup() {
  b2Vec2 gravity(0, 10);
  world_ = new b2World(gravity);
  world_->SetContactListener(this);
  //CreateGround();
  CreatePlayer();
  meteor_timer.start();
  wave_timer.start();
  is_barrier_made = false;
  has_wave_four_timer_started = false;
}
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

void Engine::CreatePlayer() {
  player = new mylibrary::Player(world_);
}

void Engine::CreateBarrier() {
  barrier = new mylibrary::Barrier(world_);
  is_barrier_made = true;
}

void Engine::reset() {
  world_->DestroyBody(player->player_body);
  delete player;
  delete barrier;
  delete world_;
  meteors.clear();
  meteor_timer.stop();
  wave_timer.stop();
  wave_four_timer.stop();
  has_proper_contact_occured = false;
  is_barrier_made = false;
  has_wave_four_timer_started = false;
}

void Engine::AddMeteor(mylibrary::Wave wave) {
  meteors.emplace_back(world_, 0.2f, wave, wave_four_timer.getSeconds());
}

std::vector<Meteor> Engine::GetMeteors() {
  return meteors;
}

mylibrary::Player* Engine::GetPlayer() {
  return player;
}

mylibrary::Barrier* Engine::GetBarrier() {
  return barrier;
}

mylibrary::Wave Engine::GetWave() {
  return current_wave;
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

  SetWave();

  if (meteor_timer.getSeconds() >= time_counter) {
    AddMeteor(current_wave);
    meteor_timer.stop();
    meteor_timer.start();
  }

  if (current_wave != mylibrary::Wave::kWaveFour) {
    RemoveOffScreenMeteors();
  }
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
  float window_height_meters = mylibrary::Conversions::pointsToMeters(cinder::app::getWindowHeight());
  float window_width_meters = mylibrary::Conversions::pointsToMeters(cinder::app::getWindowWidth());

  b2Body* node = world_->GetBodyList();

  while (node)
  {
    b2Body* b = node;
    node = node->GetNext();
    if (b->GetType() == b2_dynamicBody) {
      if (b->GetPosition().x - 0.2f > window_width_meters
          || b->GetPosition().x + 0.2f < 0
          || b->GetPosition().y - 0.2f > window_height_meters) {
        world_->DestroyBody(b);
      }
    }
  }

  meteors.erase(
      std::remove_if(
          meteors.begin(),
          meteors.end(),
          [window_width_meters, window_height_meters](Meteor const & meteor) {
            return meteor.meteor_body->GetPosition().x - 0.2f > window_width_meters
            || meteor.meteor_body->GetPosition().x + 0.2f < 0
            || meteor.meteor_body->GetPosition().y - 0.2f > window_height_meters;
          }
      ),
      meteors.end()
  );

}

void Engine::SetWave() {
  int num = static_cast<int>(std::floor(wave_timer.getSeconds()));
  switch (num / 6) {
    case 0:
      time_counter = 1;
      current_wave = mylibrary::Wave::kWaveOne;
      break;

    case 1:
      time_counter = 1;
      current_wave = mylibrary::Wave::kWaveTwo;
      break;

    case 2:
      time_counter = 1;
      current_wave = mylibrary::Wave::kWaveThree;

      if (!is_barrier_made) {
        CreateBarrier();
      }
      break;

    case 3:
      if (!has_wave_four_timer_started) {
        wave_four_timer.start();
        has_wave_four_timer_started = true;
      }
      time_counter = 0.4;
      current_wave = mylibrary::Wave::kWaveFour;
      break;

    default:
      break;
  }
}

}  // namespace mylibrary