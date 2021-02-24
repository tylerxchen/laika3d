#include "../src/renderer/renderer.hpp"
#include "../src/scene/transformationnode.hpp"
#include "../src/assets/resourcemanager.hpp"

#include <iostream>

int main() {
  using namespace laika3d;

  Renderer ren(1024, 600);
  ResourceManager rm;
  Scene s;

  std::dynamic_pointer_cast<TransformationNode>(s.find_node("root"))->set_translation(glm::vec3(2.5f, 0.0, -10.0f));

  {
    auto tex_opt = rm.load<Texture>("res/textures/single_pixel_gray.png");
    assert(tex_opt.has_value());
    auto tex = *tex_opt;

    auto suzanne_opt = rm.load<Mesh>("res/models/suzanne.obj");
    assert(suzanne_opt.has_value());
    auto suzanne = *suzanne_opt;

    auto shader_opt = rm.load<Shader>("res/shaders/shader.glsl");
    assert(shader_opt.has_value());
    auto shader = *shader_opt;

    auto suzanne_node = std::make_shared<GeometryNode>("suzanne");
    suzanne_node->mesh = suzanne;
    suzanne_node->texture = tex;
    suzanne_node->shader = shader;

    s.add_node("root", suzanne_node);
  }

  ren.loop(
    [&]() {
      // draw the scene
      ren.draw(s);
    }
  );
}

