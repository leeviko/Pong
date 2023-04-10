#include "Game.hpp"
#include "ResourceManager.hpp"

Game::Game(unsigned int width, unsigned int height) : m_Width(width), m_Height(height), m_PlaneWidth(150.0f)
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
}

void Game::Update(float dt)
{
  ResourceManager::GetShader("quad").Use();

  glm::mat4 proj = glm::ortho(0.0f, static_cast<float>(m_Width), static_cast<float>(m_Height), 0.0f, -1.0f, 1.0f);

  ResourceManager::GetShader("quad").SetMatrix4("u_MVP", proj, false);

  GameRenderer.BeginBatch();

  GameRenderer.DrawQuad({0.0f, m_Height / 2.0f - m_PlaneWidth / 2}, {15.0f, m_PlaneWidth}, {0.8f, 0.8f, 0.8f, 1.0f});
  GameRenderer.DrawQuad({m_Width - 15.0f, m_Height / 2.0f - m_PlaneWidth / 2}, {15.0f, m_PlaneWidth}, {0.8f, 0.8f, 0.8f, 1.0f});

  GameRenderer.EndBatch();
  GameRenderer.Flush();
}