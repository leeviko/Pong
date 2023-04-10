#pragma once

#include <glad/glad.h>
#include <map>
#include <string>
#include "Shader.hpp"

class ResourceManager
{
public:
  static std::map<std::string, Shader> Shaders;

  static Shader LoadShader(const char *vShaderFile, const char *fShaderFile, std::string name);
  static Shader GetShader(std::string name);

  static void Clear();

private:
  ResourceManager() {}
  static Shader loadShaderFromFile(const char *vShaderFile, const char *fShaderFile);
};