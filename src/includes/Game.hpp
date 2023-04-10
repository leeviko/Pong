#pragma once
#include "Renderer.hpp"

class Game
{
private:
  unsigned int m_Width, m_Height;
  float m_PlaneWidth;
  Renderer GameRenderer;

public:
  Game(unsigned int width, unsigned int height);
  ~Game();

  void Init();
  void Update(float dt);
};