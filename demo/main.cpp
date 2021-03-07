#include "../src/renderer/renderer.hpp"
#include "../src/scene/transformationnode.hpp"
#include "../src/assets/resourcemanager.hpp"

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

  std::dynamic_pointer_cast<TransformationNode>(s.find_node("root"))->set_translation(glm::vec3(2.5f, 0.0, -10.0f));

  ren.set_key_callback(key_callback);

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

      ImGui::ShowDemoWindow();

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
        ImGui::End();
      }

      // render imgui
      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
  );
}

