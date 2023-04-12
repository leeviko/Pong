#include "Ball.hpp"
#include <random>
#include <iostream>

void Ball::Init(unsigned int winWidth, unsigned int winHeight)
{
  std::random_device rd;
  std::mt19937 gen(rd());

  std::uniform_real_distribution<float> dis(-1.0f, 1.0f);

  float randX = dis(gen);
  float randY = dis(gen);

  this->winWidth = winWidth;
  this->winHeight = winHeight;
  this->speed = 300.0f;
  this->velocity = {randX, randY};
  this->Pos = {(float)winWidth / 2.0f, (float)winHeight / 2.0f};
}
void Ball::CheckCollision(GameObject *enemy, GameObject *player)
{
  if (this->Pos.y <= 0.0f)
  {
    glm::vec2 borderNormal = {0.0f, 1.0f};
    glm::vec2 reflectedVel = glm::reflect(this->velocity, borderNormal);
    this->Pos += reflectedVel;
    this->velocity = reflectedVel;
    return;
  }
  if (this->Pos.y + this->Size.y >= (float)winHeight)
  {
    glm::vec2 borderNormal = {0.0f, -1.0f};
    glm::vec2 reflectedVel = glm::reflect(this->velocity, borderNormal);
    this->Pos += reflectedVel;
    this->velocity = reflectedVel;
    return;
  }

  if (this->Pos.x <= enemy->Size.x && this->Pos.y >= enemy->Pos.y && this->Pos.y <= enemy->Pos.y + enemy->Size.y)
  {
    glm::vec2 planeNormal = {-1.0f, 0.0f};
    glm::vec2 reflectedVel = glm::reflect(this->velocity, planeNormal);
    this->Pos += reflectedVel;
    this->velocity = reflectedVel;
    return;
  }

  if (this->Pos.x + this->Size.x >= player->Pos.x && this->Pos.y >= player->Pos.y && this->Pos.y <= player->Pos.y + player->Size.y)
  {
    glm::vec2 planeNormal = {1.0f, 0.0f};
    glm::vec2 reflectedVel = glm::reflect(this->velocity, planeNormal);
    this->Pos += reflectedVel;
    this->velocity = reflectedVel;
    return;
  }
}

void Ball::Move(float dt)
{
  glm::vec2 normalizedVel = glm::normalize(this->velocity);

  this->Pos = this->Pos + normalizedVel * this->speed * dt;
}
