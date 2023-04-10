#include "Renderer.hpp"
#include "MyMath.hpp"

class GameObject
{
private:
  glm::vec2 pos, size;
  glm::vec3 color;

public:
  void Draw();
};
