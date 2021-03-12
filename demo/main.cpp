#include "../src/renderer/renderer.hpp"
#include "../src/scene/transformationnode.hpp"
#include "../src/assets/resourcemanager.hpp"
#include "../src/assets/material_presets.hpp"

#include <iostream>
#include <stack>

static const float MOVE_SPEED = 0.3f;

static const float ROTATE_SPEED = 0.05f;

// (x, y, z)
static glm::vec3 move_vector(0.0f, 0.0f, 0.0f);

// (yaw, pitch)
static glm::vec2 turn_vector(0.0f, 0.0f);

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  switch (key) {
    // camera translation
    case GLFW_KEY_A:
      move_vector[0] = (action == GLFW_RELEASE) ? 0.0f : -1.0f;
      break;
    case GLFW_KEY_D:
      move_vector[0] = (action == GLFW_RELEASE) ? 0.0f : 1.0f;
      break;
    case GLFW_KEY_W:
      move_vector[2] = (action == GLFW_RELEASE) ? 0.0f : -1.0f;
      break;
    case GLFW_KEY_S:
      move_vector[2] = (action == GLFW_RELEASE) ? 0.0f : 1.0f;
      break;
    case GLFW_KEY_SPACE:
      move_vector[1] = (action == GLFW_RELEASE) ? 0.0f : 1.0f;
      break;
    case GLFW_KEY_LEFT_SHIFT:
    case GLFW_KEY_RIGHT_SHIFT:
      move_vector[1] = (action == GLFW_RELEASE) ? 0.0f : -1.0f;
      break;
    // camera rotation
    case GLFW_KEY_LEFT:
      turn_vector[0] = (action == GLFW_RELEASE) ? 0.0f : 1.0f;
      break;
    case GLFW_KEY_RIGHT:
      turn_vector[0] = (action == GLFW_RELEASE) ? 0.0f : -1.0f;
      break;
    case GLFW_KEY_UP:
      turn_vector[1] = (action == GLFW_RELEASE) ? 0.0f : 1.0f;
      break;
    case GLFW_KEY_DOWN:
      turn_vector[1] = (action == GLFW_RELEASE) ? 0.0f: -1.0f;
      break;
  }
}



int main() {
  using namespace laika3d;

  Renderer ren(1024 * 3, 600 * 3);
  ResourceManager rm;
  Scene s;

  //std::dynamic_pointer_cast<TransformationNode>(s.find_node("root"))->set_translation(glm::vec3(2.5f, 0.0, -10.0f));

  ren.set_key_callback(key_callback);

  {
    auto suzanne_transformation = std::make_shared<TransformationNode>("suzanne_trans");
    suzanne_transformation->set_translation(glm::vec3(2.5f, 0.0f, -10.0f));
    s.add_node("root", suzanne_transformation);

    auto tex_opt = rm.load<Texture>("res/textures/single_pixel_gray.png");
    assert(tex_opt.has_value());
    auto tex = *tex_opt;

    auto suzanne_opt = rm.load<Mesh>("res/models/suzanne.obj");
    assert(suzanne_opt.has_value());
    auto suzanne = *suzanne_opt;

    auto shader_opt = rm.load<Shader>("res/shaders/shader.glsl");
    assert(shader_opt.has_value());
    auto shader = *shader_opt;

    auto suzanne_node = std::make_shared<GeometryNode>("suzanne_model");
    suzanne_node->mesh = suzanne;
    suzanne_node->texture = tex;
    suzanne_node->shader = shader;
    suzanne_node->material = std::make_shared<Material>(JADE);

    s.add_node("suzanne_trans", suzanne_node);

    auto floor_transformation = std::make_shared<TransformationNode>("floor_trans");
    floor_transformation->set_translation(glm::vec3(0.0f, -2.0f, 0.0f));
    floor_transformation->set_scale(glm::vec3(20.0f, 1.0f, 20.0f));
    s.add_node("root", floor_transformation);
    
    auto cube_opt = rm.load<Mesh>("res/models/cube.obj");
    assert(cube_opt.has_value());
    auto cube = *cube_opt;

    auto cube_node = std::make_shared<GeometryNode>("floor_model");
    cube_node->mesh = cube;
    cube_node->texture = tex;
    cube_node->shader = shader;
    cube_node->material = std::make_shared<Material>(GOLD);
    s.add_node("floor_trans", cube_node);

    auto teapot_transformation = std::make_shared<TransformationNode>("teapot_trans");
    teapot_transformation->set_translation(glm::vec3(-5.0f, 0.0f, -8.0f));
    teapot_transformation->rotate_y(glm::radians(180.0f));
    s.add_node("root", teapot_transformation);

    auto teapot_opt = rm.load<Mesh>("res/models/teapot.obj");
    assert(teapot_opt.has_value());
    auto teapot = *teapot_opt;

    auto teapot_node = std::make_shared<GeometryNode>("teapot_model");
    teapot_node->mesh = teapot;
    teapot_node->texture = tex;
    teapot_node->shader = shader;
    teapot_node->material = std::make_shared<Material>(JADE);
    s.add_node("teapot_trans", teapot_node);
  }

  ren.loop(
    [&]() {
      // handle camera movement
      auto angular_velocity = ROTATE_SPEED * turn_vector;
      s.cam.rotate_y(angular_velocity[0]);
      s.cam.rotate_x(angular_velocity[1]);
      
      auto velocity = MOVE_SPEED * move_vector;
      s.cam.translate(velocity[0], velocity[1], velocity[2]);

      // draw the scene
      ren.draw(s);

      // gui setup
      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();

      //ImGui::ShowDemoWindow();

      {
        ImGui::Begin("Scene Graph");
        
        // simple depth first traversal of the scene graph to generate the menu
        struct SceneFrame {
          bool opened;
          std::shared_ptr<SceneNode> node;
        };

        std::stack<SceneFrame> scene_stack;
        scene_stack.push({ false, s.root });

        while (!scene_stack.empty()) {
          auto& curr = scene_stack.top();
          if (!curr.opened) {
            if (ImGui::TreeNode(curr.node->get_name().c_str())) {
              // if the node is open, we should traverse further while also remembering to pop the treenode
              curr.opened = true;
              if (curr.node->get_child_count() > 0) {
                for (auto it = curr.node->children_begin(); it != curr.node->children_end(); ++it) {
                  scene_stack.push({ false, (*it) });
                }
              }
            }
            else {
              // the node doesn't need to stay on the stack if it hasn't been opened, so it can be popped immediately
              scene_stack.pop();
            }
          }
          else {
            // cleanup called when returning to an opened node
            ImGui::TreePop();
            scene_stack.pop();
          }
        }
        ImGui::End();
      }

      {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Stats");

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::Text("%d vertices, %d indices (%d triangles)", ren.stats.vertices, ren.stats.indices, ren.stats.indices / 3);
        ImGui::Text("GPU Vendor: %s", glGetString(GL_VENDOR));
        ImGui::Text("GPU Name: %s", glGetString(GL_RENDERER));
        ImGui::End();
      }

      // render imgui
      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
  );
}

