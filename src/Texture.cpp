#include "Texture.hpp"
#include "Renderer.hpp"

Texture::Texture()
    : Width(0), Height(0), Internal_Format(GL_RGB), Image_Format(GL_RGB), Wrap_S(GL_REPEAT), Wrap_T(GL_REPEAT), Filter_Min(GL_LINEAR), Filter_Max(GL_LINEAR)
{
  glGenTextures(1, &m_TextureId);
}

void Texture::Generate(unsigned int width, unsigned int height, unsigned char *data)
{
  Width = width;
  Height = height;
  // create Texture
  GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureId));
  GLCall(glTexImage2D(GL_TEXTURE_2D, 0, Internal_Format, width, height, 0, Image_Format, GL_UNSIGNED_BYTE, data));
  // set Texture wrap and filter modes
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, Wrap_S));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, Wrap_T));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Filter_Min));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Filter_Max));
  // unbind texture
  GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture::Bind() const
{
  GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureId));
}
