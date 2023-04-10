#include "Renderer.hpp"
#include <iostream>

void GLClearError()
{
  while (glGetError() != GL_NO_ERROR)
    ;
}
bool GLLogCall(const char *function, const char *file, int line)
{
  while (GLenum error = glGetError())
  {
    std::cout << "[OpenGL Error] (" << error << ")"
              << " " << file << ":" << line << std::endl;
    return false;
  }
  return true;
}

RendererData s_Data;

Renderer::Renderer()
{
}
Renderer::~Renderer()
{
}

void Renderer::Init()
{
  s_Data.QuadBuffer = new Vertex[MaxVertices];

  GLCall(glGenVertexArrays(1, &s_Data.QuadVA));
  GLCall(glGenBuffers(1, &s_Data.QuadVB));

  GLCall(glBindVertexArray(s_Data.QuadVA));

  GLCall(glBindBuffer(GL_ARRAY_BUFFER, s_Data.QuadVB));
  GLCall(glBufferData(GL_ARRAY_BUFFER, MaxVertices * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW));

  GLCall(glEnableVertexAttribArray(0));
  GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Position)));
  GLCall(glEnableVertexAttribArray(1));
  GLCall(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Color)));
  GLCall(glEnableVertexAttribArray(2));
  GLCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, TexCoords)));
  GLCall(glEnableVertexAttribArray(3));
  GLCall(glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, TexIndex)));

  unsigned int indices[MaxIndices];

  unsigned int offset = 0;
  for (int i = 0; i < MaxIndices; i += 6)
  {
    indices[i + 0] = 0 + offset;
    indices[i + 1] = 1 + offset;
    indices[i + 2] = 2 + offset;
    indices[i + 3] = 2 + offset;
    indices[i + 4] = 3 + offset;
    indices[i + 5] = 0 + offset;

    offset += 4;
  }

  GLCall(glGenBuffers(1, &s_Data.QuadIB));
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_Data.QuadIB));
  GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

  GLCall(glGenTextures(1, &s_Data.WhiteTextureId));
  GLCall(glBindTexture(GL_TEXTURE_2D, s_Data.WhiteTextureId));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

  unsigned int color = 0xffffffff;
  GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &color));

  s_Data.TextureSlots[0] = s_Data.WhiteTextureId;
  for (int i = 1; i < MaxTextureSlots; i++)
  {
    s_Data.TextureSlots[i] = 0;
  }

  GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void Renderer::BeginBatch()
{
  s_Data.QuadBufferPtr = s_Data.QuadBuffer;
}
void Renderer::EndBatch()
{
  GLsizeiptr size = (uint8_t *)s_Data.QuadBufferPtr - (uint8_t *)s_Data.QuadBuffer;
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, s_Data.QuadVB));
  GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, size, s_Data.QuadBuffer));
}
void Renderer::Flush()
{
  for (unsigned int i = 0; i < s_Data.TextureIndex; i++)
  {
    GLCall(glActiveTexture(GL_TEXTURE0 + i));
    GLCall(glBindTexture(GL_TEXTURE_2D, s_Data.TextureSlots[i]));
  }

  GLCall(glBindVertexArray(s_Data.QuadVA));
  GLCall(glDrawElements(GL_TRIANGLES, s_Data.IndexCount, GL_UNSIGNED_INT, 0));

  s_Data.IndexCount = 0;
  s_Data.TextureIndex = 1;

  GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
void Renderer::DrawQuad(const glm::vec2 &pos, const glm::vec2 &size, const glm::vec4 &color)
{
  if (s_Data.IndexCount >= MaxIndices)
  {
    EndBatch();
    Flush();
    BeginBatch();
  }

  float textureIndex = 0.0f;

  s_Data.QuadBufferPtr->Position = {pos.x, pos.y, 0.0f};
  s_Data.QuadBufferPtr->Color = color;
  s_Data.QuadBufferPtr->TexCoords = {0.0f, 0.0f};
  s_Data.QuadBufferPtr->TexIndex = textureIndex;
  s_Data.QuadBufferPtr++;

  s_Data.QuadBufferPtr->Position = {pos.x + size.x, pos.y, 0.0f};
  s_Data.QuadBufferPtr->Color = color;
  s_Data.QuadBufferPtr->TexCoords = {1.0f, 0.0f};
  s_Data.QuadBufferPtr->TexIndex = textureIndex;
  s_Data.QuadBufferPtr++;

  s_Data.QuadBufferPtr->Position = {pos.x + size.x, pos.y + size.y, 0.0f};
  s_Data.QuadBufferPtr->Color = color;
  s_Data.QuadBufferPtr->TexCoords = {1.0f, 1.0f};
  s_Data.QuadBufferPtr->TexIndex = textureIndex;
  s_Data.QuadBufferPtr++;

  s_Data.QuadBufferPtr->Position = {pos.x, pos.y + size.y, 0.0f};
  s_Data.QuadBufferPtr->Color = color;
  s_Data.QuadBufferPtr->TexCoords = {0.0f, 1.0f};
  s_Data.QuadBufferPtr->TexIndex = textureIndex;
  s_Data.QuadBufferPtr++;

  s_Data.IndexCount += 6;
}
