#pragma once

#include "scenenode.hpp"
#include "../assets/mesh.hpp"
#include "../assets/texture.hpp"
#include "../assets/shader.hpp"

namespace laika3d {
  class GeometryNode : public SceneNode {
    public:
      GeometryNode();
      ~GeometryNode();

      void bind() const;
      void unbind() const;

      void set_mesh(std::shared_ptr<Mesh> m) { mesh = m; }
      void set_texture(std::shared_ptr<Texture> t) { texture = t; }
      void set_shader(std::shared_ptr<Shader> s) { shader = s; }

    private:
      std::shared_ptr<Mesh> mesh;    
      std::shared_ptr<Texture> texture;
      std::shared_ptr<Shader> shader;
  };
}
