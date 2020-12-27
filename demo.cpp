#include <iostream>
#include "tc3d/renderer.hpp"
#include "tc3d/vertexbuffer.hpp"
#include "tc3d/indexbuffer.hpp"
#include "tc3d/window.hpp"
#include "tc3d/shader.hpp"

using namespace tc3d;

int main() {
  rendering::Window win;
  rendering::Renderer ren;
  
  rendering::Shader s("res/shaders/simplevertex.shader", "res/shaders/simplefragment.shader");

  rendering::VertexBuffer vbuf = {{
    {-1.0f, -1.0f, 0.0f},
    {1.0f, -1.0f, 0.0f},
    {0.0f, 1.0f, 0.0f},
  }};

  rendering::IndexBuffer ibuf = {{
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
