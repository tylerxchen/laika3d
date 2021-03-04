#include "renderer.hpp"
#include "../scene/transformationnode.hpp"

#include <stdexcept>
#include <iostream>

using namespace laika3d;

namespace laika3d {
  void GLAPIENTRY message_callback(GLenum source, GLenum type, GLuint id, GLenum severity,
                                    GLsizei length, const GLchar* message, const void* userParam) {
    std::cout << "OpenGL message: " << message << std::endl;
  }
}

Renderer::Renderer(unsigned int width, unsigned int height) {
  glewExperimental = true;
  if (!glfwInit()) {
    throw std::runtime_error("Failed to initialize GLFW");
  }

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  win = glfwCreateWindow(width, height, "laika3d", nullptr, nullptr);

  if (win == nullptr) {
    glfwTerminate();
    throw std::runtime_error("Failed to open a GLFW window. Check your version of OpenGL");
  }

  glfwMakeContextCurrent(win);
  if (glewInit() != GLEW_OK) {
    throw std::runtime_error("Failed to initialize GLEW");
  }

  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glDebugMessageCallback(message_callback, nullptr);
  glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
  glGenVertexArrays(1, &vao_id);
  glBindVertexArray(vao_id);

  // dear imgui setup
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;

  ImGui::StyleColorsDark();

  ImGui::GetIO().FontGlobalScale = 2.0;

  ImGui_ImplGlfw_InitForOpenGL(win, true);
  ImGui_ImplOpenGL3_Init("#version 130");
}

Renderer::~Renderer() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(win);
  glfwTerminate();
}

void Renderer::draw(const Scene& scene) {
  glm::mat4 mat_state(1.0f);
  draw_impl(scene, scene.root, mat_state);
}

void Renderer::set_key_callback(void (*key_callback)(GLFWwindow*, int, int, int, int)) {
  glfwSetKeyCallback(win, key_callback);
}

void Renderer::draw_impl(const Scene& scene, std::shared_ptr<SceneNode> root, glm::mat4& state) {
  if (typeid(*root) == typeid(TransformationNode)) {
    // apply the transformation
    auto trans_node = std::dynamic_pointer_cast<TransformationNode>(root);
    state *= trans_node->get_model_matrix();
  }
  else if (typeid(*root) == typeid(GeometryNode)) {
    // draw the node
    auto geo_node = std::dynamic_pointer_cast<GeometryNode>(root);

    geo_node->bind();
    geo_node->set_mvp(state, scene.cam.get_view(), scene.cam.get_proj());

    glEnableVertexAttribArray(VERTEX_POSITION);
    glVertexAttribPointer(
      VERTEX_POSITION,
      3,
      GL_FLOAT,
      GL_FALSE,
      sizeof(Vertex),
      nullptr
    );
    
    glEnableVertexAttribArray(VERTEX_NORMAL);
    glVertexAttribPointer(
      VERTEX_NORMAL,
      3,
      GL_FLOAT,
      GL_FALSE,
      sizeof(Vertex),
      reinterpret_cast<void*>(offsetof(Vertex, norm_x))
    );

    glEnableVertexAttribArray(TEXTURE_COORDINATE);
    glVertexAttribPointer(
      TEXTURE_COORDINATE,
      3,
      GL_FLOAT,
      GL_FALSE,
      sizeof(Vertex),
      reinterpret_cast<void*>(offsetof(Vertex, tex_x))
    );

    glDrawElements(
      GL_TRIANGLES,
      geo_node->mesh->v_index_count(),
      GL_UNSIGNED_INT,
      nullptr
    );

    glDisableVertexAttribArray(VERTEX_POSITION);
    glDisableVertexAttribArray(VERTEX_NORMAL);
    glDisableVertexAttribArray(TEXTURE_COORDINATE);
  }

  // explore all of the children
  for (auto it = root->children_begin(); it != root->children_end(); ++it) {
    draw_impl(scene, *it, state);
  }

  if (typeid(*root) == typeid(TransformationNode)) {
    // each transformation node needs to undo itself after all its children have been explored
    auto trans_node = std::dynamic_pointer_cast<TransformationNode>(root);
    state *= glm::inverse(trans_node->get_model_matrix());
  }
}

void Renderer::loop(std::function<void()> frame_callback) {
  while (!glfwWindowShouldClose(win)) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    frame_callback();
    glfwSwapBuffers(win);
    glfwPollEvents();
  }
}
