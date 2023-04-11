#pragma once
#include "Shader.hpp"
#include "MyMath.hpp"
#include <array>
#include "Texture.hpp"
#include "Macros.hpp"

void GLClearError();
bool GLLogCall(const char *function, const char *file, int line);

static const unsigned int MaxQuads = 1000;
static const unsigned int MaxVertices = MaxQuads * 4;
static const unsigned int MaxIndices = MaxQuads * 6;
static const unsigned int MaxTextureSlots = 32;

struct Vertex
{
  glm::vec3 Position;
  glm::vec4 Color;
  glm::vec2 TexCoords;
  float TexIndex;
};

class Renderer
{
public:
  Renderer();
  ~Renderer();

  void Init();
  void BeginBatch();
  void EndBatch();
  void Flush();
  void DrawQuad(const glm::vec2 &pos, const glm::vec2 &size, const glm::vec4 &color);
  void DrawQuad(const glm::vec2 &pos, const glm::vec2 &size, unsigned int textureId);
};
