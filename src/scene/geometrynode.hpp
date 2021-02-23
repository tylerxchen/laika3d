#pragma once

#include "scenenode.hpp"
#include "../assets/mesh.hpp"
#include "../assets/texture.hpp"
#include "../assets/shader.hpp"
#include <glm/glm.hpp>

namespace laika3d {
  struct GeometryNode : public SceneNode {
    public:
      GeometryNode(const std::string& n);
      ~GeometryNode();

      void bind() const;
      void unbind() const;

      void set_mvp(const glm::mat4& mvp);
      std::shared_ptr<Mesh> mesh;    
      std::shared_ptr<Texture> texture;
      std::shared_ptr<Shader> shader;
  };
}
