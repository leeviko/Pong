#include "GameObject.hpp"

GameObject::GameObject(Renderer &renderer) : renderer(&renderer), Pos({0.0f, 0.0f}), Color({1.0f, 1.0f, 1.0f, 1.0f}), Size({1.0f, 1.0f})
{
}
GameObject::~GameObject()
{
}
void GameObject::Draw()
{
  renderer->DrawQuad(Pos, Size, Color);
}