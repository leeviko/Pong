#include "Game.hpp"
#include "ResourceManager.hpp"
#include "GameObject.hpp"
#include "Ball.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

Game::Game(unsigned int width, unsigned int height) : m_Width(width), m_Height(height), m_PlayerPlane(GameRenderer), m_Ball(GameRenderer), m_EnemyPlane(GameRenderer)
{
}

Game::~Game()
{
}

void Game::Init()
{
  ResourceManager::LoadShader("D:/Dev/Cpp/OpenGL/pong/src/shaders/shader.vert", "D:/Dev/Cpp/OpenGL/pong/src/shaders/shader.frag", "quad");

  int samplers[32];
  for (unsigned int i = 0; i < 32; i++)
  {
    samplers[i] = i;
  }

  ResourceManager::GetShader("quad").Use();
  ResourceManager::GetShader("quad").SetIntegerv("u_Textures", samplers, false);

  Renderer renderer;
  GameRenderer = renderer;

  GameRenderer.Init();

  ResourceManager::LoadTexture("D:/Dev/Cpp/OpenGL/pong/src/assets/ball.png", true, "ball");

  Ball Ball(GameRenderer);
  m_Ball = Ball;
  m_Ball.Pos = {m_Width / 2.0f, m_Height / 2.0f};
  m_Ball.Size = {25.0f, 25.0f};
  m_Ball.Color = {1.0f, 0.5f, 0.6f, 1.0f};
  m_Ball.TextureId = ResourceManager::GetTexture("ball").m_TextureId;
  m_Ball.Init();

  GameObject PlayerPlane(GameRenderer);
  m_PlayerPlane = PlayerPlane;

  m_PlayerPlane.Size = {15.0f, 150.0f};
  m_PlayerPlane.Pos = {m_Width - m_PlayerPlane.Size.x,
                       m_Height / 2.0f - m_PlayerPlane.Size.y / 2};
  m_PlayerPlane.Color = {0.8f, 0.8f, 0.8f, 1.0f};

  GameObject EnemyPlane(GameRenderer);
  m_EnemyPlane = PlayerPlane;

  m_EnemyPlane.Size = {15.0f, 150.0f};
  m_EnemyPlane.Pos = {0,
                      m_Height / 2.0f - m_EnemyPlane.Size.y / 2};
  m_EnemyPlane.Color = {0.8f, 0.8f, 0.8f, 1.0f};
}

void Game::Update(float dt)
{
  ResourceManager::GetShader("quad").Use();

  glm::mat4 proj = glm::ortho(0.0f, static_cast<float>(m_Width), static_cast<float>(m_Height), 0.0f, -1.0f, 1.0f);

  ResourceManager::GetShader("quad").SetMatrix4("u_MVP", proj, false);

  GameRenderer.BeginBatch();
  m_PlayerPlane.Draw();
  m_EnemyPlane.Draw();

  m_Ball.Draw();
  m_Ball.CheckCollision(&m_EnemyPlane, &m_PlayerPlane);
  m_Ball.Move(dt);
  GameRenderer.EndBatch();
  GameRenderer.Flush();
}

void Game::ProcessInput(float dt, int isUpPressed, int isDownPressed)
{
  float velocity = 400.0f;
  if (isUpPressed == GLFW_PRESS)
  {
    if (m_PlayerPlane.Pos.y <= 0.0f)
    {
      m_PlayerPlane.Pos.y = 0.0f;
      return;
    }
    m_PlayerPlane.Pos.y -= velocity * dt;
  }
  else if (isDownPressed == GLFW_PRESS)
  {
    if (m_PlayerPlane.Pos.y >= m_Height - m_PlayerPlane.Size.y)
    {
      m_PlayerPlane.Pos.y = m_Height - m_PlayerPlane.Size.y;
      return;
    }

    m_PlayerPlane.Pos.y += velocity * dt;
  }
}
