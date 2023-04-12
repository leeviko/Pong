#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Game.hpp"

unsigned int SCREEN_WIDTH = 960;
unsigned int SCREEN_HEIGHT = 540;

int main()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong", NULL, NULL);
  if (window == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    glfwTerminate();
    return -1;
  }

  Game Pong(SCREEN_WIDTH, SCREEN_HEIGHT);

  Pong.Init();

  float lastFrame = 0.0f;
  float deltaTime = 0.0f;

  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

  while (!glfwWindowShouldClose(window))
  {
    glClear(GL_COLOR_BUFFER_BIT);

    float currFrame = glfwGetTime();
    deltaTime = currFrame - lastFrame;
    lastFrame = currFrame;

    int upKeyState = glfwGetKey(window, GLFW_KEY_UP);
    int downKeyState = glfwGetKey(window, GLFW_KEY_DOWN);
    int rKeyState = glfwGetKey(window, GLFW_KEY_R);

    Pong.ProcessInput(deltaTime, upKeyState, downKeyState, rKeyState);

    Pong.Update(deltaTime);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
