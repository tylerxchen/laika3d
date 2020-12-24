#include <iostream>
#include "rendering/renderer.hpp"
#include "rendering/vertexbuffer.hpp"
#include "rendering/indexbuffer.hpp"
#include "rendering/window.hpp"

using namespace tc3d;

int main() {
  rendering::Window win;
  rendering::Renderer ren;

  rendering::VertexBuffer vbuf = {{
    {-1.0f, -1.0f, 0.0f},
    {1.0f, -1.0f, 0.0f},
    {0.0f, 1.0f, 0.0f},
  }};

  rendering::IndexBuffer ibuf = {{
    0,
    1,
    2
  }};

  auto draw_cb = [=]() {
    ren.draw(vbuf, ibuf);
  };

  win.loop();

  return 0;
}