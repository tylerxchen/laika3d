#include <iostream>
#include "laika3d/renderer.hpp"
#include "laika3d/vertexbuffer.hpp"
#include "laika3d/indexbuffer.hpp"
#include "laika3d/window.hpp"
#include "laika3d/shader.hpp"

using namespace laika3d;

int main() {
  Window win;
  Renderer ren;
  
  Shader s("res/shaders/simplevertex.shader", "res/shaders/simplefragment.shader");

  VertexBuffer vbuf = {{
    {-1.0f, -1.0f, 0.0f},
    {1.0f, -1.0f, 0.0f},
    {0.0f, 1.0f, 0.0f},
  }};

  IndexBuffer ibuf = {{
    0,
    1,
    2,
  }};

  auto draw_cb = [&]() {
    ren.draw(vbuf, ibuf, s);
  };

  win.set_callback(draw_cb);

  win.loop();

  return 0;
}