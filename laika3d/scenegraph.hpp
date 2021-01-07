#pragma once

#include <glm/glm.hpp>

#include "mesh.hpp"
#include "texture.hpp"
#include "shader.hpp"

#include <memory>
#include <optional>

namespace laika3d {
  class SceneNode {
    public:
      SceneNode(const std::string& n);
      ~SceneNode();

      void set_translation(float x, float y, float z);
      void set_rotation_x(float angle);
      void set_rotation_y(float angle);
      void set_rotation_z(float angle);
      void set_scale(float x, float y, float z);

      glm::mat4 get_model() const { return model; }

      void set_mesh(std::shared_ptr<Mesh> m) { mesh = m; }
      void set_texture(std::shared_ptr<Texture> t) { texture = t; }
      void set_shader(std::shared_ptr<Shader> s) { shader = s; }

      std::shared_ptr<Mesh> get_mesh() const { return mesh; }
      std::shared_ptr<Texture> get_texture() const { return texture; }
      std::shared_ptr<Shader> get_shader() const { return shader; }

      std::vector<std::shared_ptr<SceneNode>>::const_iterator child_begin() const { return children.begin(); }
      std::vector<std::shared_ptr<SceneNode>>::const_iterator child_end() const { return children.end(); }

      std::optional<std::shared_ptr<SceneNode>> add_child(const std::string& child_name);
      bool delete_child(const std::string& child_name);

    private:
      // resources
      std::shared_ptr<Mesh> mesh;
      std::shared_ptr<Texture> texture;
      std::shared_ptr<Shader> shader;

      // tree stuff
      std::string name;
      std::weak_ptr<SceneNode> parent;
      std::vector<std::shared_ptr<SceneNode>> children;

      // transformations
      glm::mat4 translation;
      glm::mat4 rotation;
      glm::mat4 scaling;
      glm::mat4 model;

      void calc_model_mat();
  };

  // utils
  std::optional<std::shared_ptr<SceneNode>> find_scene_node(std::shared_ptr<SceneNode> root, const std::string& ancestor_name);
  bool delete_scene_node(std::shared_ptr<SceneNode> root, const std::string& ancestor_name);
}
