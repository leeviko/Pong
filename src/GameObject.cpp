#include "GameObject.hpp"
#include <iostream>

GameObject::GameObject(Renderer &renderer) : renderer(&renderer), Pos({0.0f, 0.0f}),
                                             Color({1.0f, 1.0f, 1.0f, 1.0f}), Size({1.0f, 1.0f}), TextureId(0.0f)
{
}
GameObject::~GameObject()
{
}
void GameObject::Draw()
{
  if (TextureId == 0.0f)
  {
    renderer->DrawQuad(Pos, Size, Color);
  }
  else
  {
    renderer->DrawQuad(Pos, Size, TextureId);
  }
}
