//
// Created by vikra on 4/28/2020.
//

#include <mylibrary/engine.h>

namespace mylibrary {

void Engine::Setup() {
  int gravity_force = 10;
  b2Vec2 gravity(0, gravity_force);
  world_ = new b2World(gravity);
  world_->SetContactListener(this);

  CreatePlayer();

  meteor_timer.start();
  wave_timer.start();

  is_barrier_made = false;
  has_wave_four_timer_started = false;
  current_wave = mylibrary::Wave::kWaveOne;
}

void Engine::CreatePlayer() {
  player = new mylibrary::Player(world_);
}

void Engine::CreateBarrier() {
  barrier = new mylibrary::Barrier(world_);
  is_barrier_made = true;
}

void Engine::Reset() {
  world_->DestroyBody(player->player_body);
  delete player;

  if (current_wave == mylibrary::Wave::kWaveThree
  || current_wave == mylibrary::Wave::kWaveFour) {
      delete barrier;
  }

  delete world_;

  meteors.clear();

  meteor_timer.stop();
  wave_timer.stop();
  wave_four_timer.stop();

  is_game_over = false;
  is_barrier_made = false;
  has_wave_four_timer_started = false;

  current_wave = mylibrary::Wave::kWaveOne;
}

void Engine::AddMeteor(const mylibrary::Wave& wave) {
  const float meteor_radius = 0.2f;
  meteors.emplace_back(world_, meteor_radius, wave,
      wave_four_timer.getSeconds());
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

bool Engine::GetIsGameOver() {
  return is_game_over;
}

void Engine::MovePlayer(const Direction& direction) {
  const double player_step = 0.125;

  switch (direction) {
    case Direction::kRight:
      if (!IsPlayerOnScreenEdge(direction)) {
          player->player_body->SetTransform(
              b2Vec2(player->player_body->
              GetPosition().x + player_step,
                  player->player_body->GetPosition().y), 0);
      }
      break;

    case Direction::kLeft:
      if (!IsPlayerOnScreenEdge(direction)) {
          player->player_body->SetTransform(
              b2Vec2(player->player_body->
              GetPosition().x - player_step,
                  player->player_body->GetPosition().y), 0);
      }
      break;
  }
}

bool Engine::IsPlayerOnScreenEdge(const Direction& direction) {
  if (direction == Direction::kRight) {
    return (player->player_body->GetPosition().x >
            Conversions::PointsToMeters(750));
  } else {
    return (player->player_body->GetPosition().x <
            Conversions::PointsToMeters(50));
  }
}

void Engine::Update() {
  float timeStep = 1.0f / 60.0f;
  int32 velocityIterations = 8;
  int32 positionIterations = 3;
  world_->Step(timeStep, velocityIterations, positionIterations);

  SetWave();

  if (meteor_timer.getSeconds() >= rate_of_meteor_drops) {
    AddMeteor(current_wave);
    meteor_timer.stop();
    meteor_timer.start();
  }

  if (current_wave != mylibrary::Wave::kWaveFour) {
    RemoveOffScreenMeteors();
  }
}

void Engine::BeginContact( b2Contact* contact ) {
  const float player_density = player->density;

  void* body_one = contact->GetFixtureA()->GetBody()->GetUserData();
  void* body_two = contact->GetFixtureB()->GetBody()->GetUserData();

  if (body_one == nullptr || body_two == nullptr) {
    return;
  }

  if (contact->GetFixtureA()->GetDensity() == player_density
  || contact->GetFixtureB()->GetDensity() == player_density) {
    is_game_over = true;
  }
}

void Engine::RemoveOffScreenMeteors() {
  float scaled_height =
      Conversions::PointsToMeters(cinder::app::getWindowHeight());
  float scaled_width =
      Conversions::PointsToMeters(cinder::app::getWindowWidth());
  const float meteor_radius = 0.2f;

  b2Body* node = world_->GetBodyList();

  while (node)
  {
    b2Body* b = node;
    node = node->GetNext();
    if (b->GetType() == b2_dynamicBody) {
      if (b->GetPosition().x - meteor_radius > scaled_width
      || b->GetPosition().x + meteor_radius < 0
          || b->GetPosition().y - meteor_radius > scaled_height) {
        world_->DestroyBody(b);
      }
    }
  }

  meteors.erase(
      std::remove_if(
          meteors.begin(),
          meteors.end(),
          [scaled_width, scaled_height, meteor_radius]
          (Meteor const & meteor) {
            return meteor.meteor_body->GetPosition().x
            - meteor_radius > scaled_width
            || meteor.meteor_body->GetPosition().x + meteor_radius < 0
            || meteor.meteor_body->GetPosition().y - meteor_radius >
                                 scaled_height;
          }
      ),
      meteors.end()
  );

}

void Engine::SetWave() {
  int num = static_cast<int>(std::floor(wave_timer.getSeconds()));
  const int wave_increments = 15;
  switch (num / wave_increments) {
    case 0:
      rate_of_meteor_drops = 1;
      current_wave = mylibrary::Wave::kWaveOne;
      break;

    case 1:
      rate_of_meteor_drops = 0.7;
      current_wave = mylibrary::Wave::kWaveTwo;
      break;

    case 2:
      rate_of_meteor_drops = 0.4;
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

      rate_of_meteor_drops = 0.2;
      current_wave = mylibrary::Wave::kWaveFour;
      break;

    default:
      is_game_over = true;
      break;
  }
}

}  // namespace mylibrary