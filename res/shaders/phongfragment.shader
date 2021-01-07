#version 330 core

out vec3 color;

void main() {
  float ambient_strength = 0.1;
  vec3 ambient = ambientStrength * lightColor;
  vec3 result = ambient * objectColor;
  FragColor = vec4(result, 1.0)
}

