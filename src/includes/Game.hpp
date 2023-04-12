#pragma once
#include "Renderer.hpp"
#include "GameObject.hpp"
#include "Ball.hpp"

class Game
{
private:
  unsigned int m_Width, m_Height;
  Renderer GameRenderer;
  GameObject m_PlayerPlane;
  GameObject m_EnemyPlane;
  Ball m_Ball;

public:
  Game(unsigned int width, unsigned int height);
  ~Game();

  void Init();
  void Update(float dt);

  void ProcessInput(float dt, int isUpPressed, int isDownPressed, int rKeyPressed);
};