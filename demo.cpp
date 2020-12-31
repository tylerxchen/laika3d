#include <glm/glm.hpp>
#include <iostream>


#include "laika3d/renderer.hpp"
#include "laika3d/vertexbuffer.hpp"
#include "laika3d/indexbuffer.hpp"
#include "laika3d/shader.hpp"
#include "laika3d/model.hpp"

using namespace laika3d;

int main() {
  Renderer ren(glm::radians(45.0f), 1024, 768, 0.1f, 100.0f);
  
  Shader s("res/shaders/simplevertex.shader", "res/shaders/simplefragment.shader");

  Model m("res/models/cube.obj");

  auto draw_cb = [&]() {
    ren.draw(m, s);
  };

  ren.set_callback(draw_cb);

  ren.loop();

  return 0;
}
