#pragma once
#include "Renderer.hpp"
#include "GameObject.hpp"

class Game
{
private:
  unsigned int m_Width, m_Height;
  Renderer GameRenderer;
  GameObject m_PlayerPlane;

public:
  Game(unsigned int width, unsigned int height);
  ~Game();

  void Init();
  void Update(float dt);

  void ProcessInput(float dt, int isUpPressed, int isDownPressed);
};