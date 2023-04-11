#include "Game.hpp"
#include "ResourceManager.hpp"
#include "GameObject.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

Game::Game(unsigned int width, unsigned int height) : m_Width(width), m_Height(height), m_PlayerPlane(GameRenderer)
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

  ResourceManager::GetShader("quad").SetIntegerv("u_Textures", samplers, false);

  Renderer renderer;
  GameRenderer = renderer;

  GameRenderer.Init();

  GameObject PlayerPlane(GameRenderer);
  m_PlayerPlane = PlayerPlane;

  m_PlayerPlane.Size = {15.0f, 150.0f};
  m_PlayerPlane.Pos = {m_Width - m_PlayerPlane.Size.x,
                       m_Height / 2.0f - m_PlayerPlane.Size.y / 2};
  m_PlayerPlane.Color = {0.8f, 0.8f, 0.8f, 1.0f};
}

void Game::Update(float dt)
{
  ResourceManager::GetShader("quad").Use();

  glm::mat4 proj = glm::ortho(0.0f, static_cast<float>(m_Width), static_cast<float>(m_Height), 0.0f, -1.0f, 1.0f);

  ResourceManager::GetShader("quad").SetMatrix4("u_MVP", proj, false);

  GameRenderer.BeginBatch();
  m_PlayerPlane.Draw();

  GameRenderer.EndBatch();
  GameRenderer.Flush();
}

void Game::ProcessInput(float dt, int isUpPressed, int isDownPressed)
{
  float velocity = 400.0f;
  if (isUpPressed == GLFW_PRESS)
  {
    std::cout << m_PlayerPlane.Pos.y << std::endl;
    if (m_PlayerPlane.Pos.y <= 0.0f)
    {
      m_PlayerPlane.Pos.y = 0.0f;
      return;
    }
    m_PlayerPlane.Pos.y -= velocity * dt;
  }
  else if (isDownPressed == GLFW_PRESS)
  {
    std::cout << m_PlayerPlane.Pos.y << std::endl;
    if (m_PlayerPlane.Pos.y >= m_Height - m_PlayerPlane.Size.y)
    {
      m_PlayerPlane.Pos.y = m_Height - m_PlayerPlane.Size.y;
      return;
    }

    m_PlayerPlane.Pos.y += velocity * dt;
  }
}
