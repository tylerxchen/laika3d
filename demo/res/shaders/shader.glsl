#VERTEX
#version 330 core

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;
layout(location = 2) in vec2 texture_coordinate;

out vec2 uv;
out vec3 frag_normal;
out vec3 frag_position;
out vec3 light_position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {
  gl_Position = proj * view * model * vec4(vertex_position, 1.0);

  uv = texture_coordinate;
  frag_normal = mat3(transpose(inverse(view * model))) * vertex_normal;
  frag_position = vec3(view * model * vec4(vertex_position, 1.0));
  // there's a hard coded light at (0.0, 0.0, 0.0) for the time being
  light_position = vec3(view * vec4(0.0, 0.0, 0.0, 1.0));
}

#FRAGMENT
#version 330 core

in vec2 uv;
in vec3 frag_normal;
in vec3 frag_position;
in vec3 light_position;

out vec4 color;

uniform sampler2D texture_sampler;

void main() {
  vec4 tex_color = texture(texture_sampler, uv);

  // ambient
  float ambient_str = 0.3;
  vec3 light_color = vec3(1.0, 1.0, 1.0);
  vec3 ambient = ambient_str * light_color;

  vec3 light_dir = normalize(light_position - frag_position);

  // diffuse
  vec3 norm = normalize(frag_normal);
  float diff = max(dot(norm, light_dir), 0.0);
  vec3 diffuse = diff * light_color;

  // specular
  float specular_str = 0.5;
  int shininess = 32;
  vec3 view_dir = normalize(-frag_position);
  vec3 halfway_dir = normalize(light_dir + view_dir);
  float spec = pow(max(dot(frag_normal, halfway_dir), 0.0), shininess);
  vec3 specular = light_color * spec;

  color = (vec4(ambient, 1.0) + vec4(diffuse, 1.0) + vec4(specular, 1.0)) * tex_color;
}
