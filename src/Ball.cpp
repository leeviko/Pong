#include "Ball.hpp"
#include <random>
#include <iostream>

void Ball::Init()
{
  std::random_device rd;
  std::mt19937 gen(rd());

  std::uniform_real_distribution<float> dis(-1.0f, 1.0f);

  float randX = dis(gen);
  float randY = dis(gen);

  this->speed = 200.0f;
  this->velocity = {randX, randY};
}
void Ball::CheckCollision(GameObject *enemy, GameObject *player)
{
  if (this->Pos.x <= 15.0f && this->Pos.y >= enemy->Pos.y && this->Pos.y <= enemy->Pos.y + 150.0f)
  {
    this->velocity = {1.0f - this->velocity.x, 1.0f - this->velocity.y};
    return;
  }

  if (this->Pos.x + this->Size.x >= player->Pos.x && this->Pos.y >= player->Pos.y && this->Pos.y <= player->Pos.y + 150.0f)
  {
    this->velocity = {1.0f - this->velocity.x, 1.0f - this->velocity.y};
    return;
  }
}

void Ball::Move(float dt)
{
  glm::vec2 normalizedVel = glm::normalize(this->velocity);

  this->Pos = this->Pos + normalizedVel * this->speed * dt;
}
