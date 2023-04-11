#pragma once

#include "GameObject.hpp"

class Ball : public GameObject
{
public:
  float speed;
  glm::vec2 velocity;

public:
  using GameObject::GameObject;

  void Init();
  void CheckCollision(GameObject *enemy, GameObject *player);
  void Move(float dt);
};
