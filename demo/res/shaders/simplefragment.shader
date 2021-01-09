#version 330 core

in vec3 uv;

out vec3 color;

uniform sampler2D texture_sampler

void main() {
  color = texture(texture_sampler, uv).rgb
}
