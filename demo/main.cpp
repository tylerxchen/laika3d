#include "../src/renderer/renderer.hpp"

#include <iostream>

int main() {
  using namespace laika3d;
  Renderer ren(1024, 600);

  ren.loop(
    []() {
      // nothing here right now
    }
  );
}

