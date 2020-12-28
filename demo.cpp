#include <iostream>
#include "laika3d/renderer.hpp"
#include "laika3d/vertexbuffer.hpp"
#include "laika3d/indexbuffer.hpp"
#include "laika3d/window.hpp"
#include "laika3d/shader.hpp"
#include "laika3d/model.hpp"

using namespace laika3d;

int main() {
  Window win;
  Renderer ren;
  
  Shader s("res/shaders/simplevertex.shader", "res/shaders/simplefragment.shader");

  Model m("res/models/cube.obj");

  auto draw_cb = [&]() {
    ren.draw(m, s);
  };

  win.set_callback(draw_cb);

  win.loop();

  return 0;
}
