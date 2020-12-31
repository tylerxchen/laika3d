#include <glm/glm.hpp>
#include <iostream>

#include "laika3d/renderer.hpp"
#include "laika3d/vertexbuffer.hpp"
#include "laika3d/indexbuffer.hpp"
#include "laika3d/shader.hpp"
#include "laika3d/model.hpp"

using namespace laika3d;

int main() {
  const unsigned int WIDTH = 1024;
  const unsigned int HEIGHT = 768;
  Renderer ren(WIDTH, HEIGHT);

  Camera c(glm::radians(45.0f), static_cast<float>(WIDTH) / HEIGHT, 0.1f, 100.0f);
  
  Shader s("res/shaders/simplevertex.shader", "res/shaders/simplefragment.shader");

  Model m("res/models/cube.obj");

  c.translate(4.0f, 0.0f, 4.0f);
  c.rotate_y(glm::radians(45.0f));

  auto draw_cb = [&]() {
    ren.draw(m, s, c);
  };

  ren.set_callback(draw_cb);

  ren.loop();

  return 0;
}
