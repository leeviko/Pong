#pragma once

#include "GameObject.hpp"

class Ball : public GameObject
{
public:
  float speed;
  glm::vec2 velocity;
  unsigned int winWidth, winHeight;

public:
  using GameObject::GameObject;

  void Init(unsigned int winWidth, unsigned int winHeight);
  void CheckCollision(GameObject *enemy, GameObject *player);
  void Move(float dt);
};
