#pragma once

#include "../scene/scenegraph.hpp"

#include <functional>

namespace laika3d {
  class Renderer {
    public:
      Renderer();
      ~Renderer();

      void draw(const SceneGraph& scene);

      void loop(std::function<void()> frame_callback);
  };
}
