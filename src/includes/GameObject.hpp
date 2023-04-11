#pragma once

#include "Renderer.hpp"
#include "MyMath.hpp"

class GameObject
{
public:
  Renderer *renderer;
  glm::vec2 Pos, Size;
  glm::vec4 Color;

  GameObject(Renderer &renderer);
  ~GameObject();

  void Draw();
};
