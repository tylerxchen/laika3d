#version 330 core

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;
layout(location = 2) in vec3 texture_coordinate;

out vec3 uv;

uniform mat4 mvp;

void main() {
  gl_Position = mvp * vec4(vertex_position, 1);

  uv = texture_coordinate;
}
