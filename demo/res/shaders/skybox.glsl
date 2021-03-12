#VERTEX
#version 330 core

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;
layout(location = 2) in vec2 texture_coordinate;

out vec2 uv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {
  gl_Position = proj * view * model * vec4(vertex_position, 1.0);
  uv = texture_coordinate;
}

#FRAGMENT
#version 330 core

in vec2 uv;

out vec4 color;

uniform sampler2D texture_sampler;

struct Material {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
};

uniform Material material;

void main() {
  material;
  color = texture(texture_sampler, uv);
}
