#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

uniform mat4 model; // Converts local object coordinates to camera coordinates
uniform mat4 view; // Converts quarter the normalized coordinates to window
uniform mat4 projection; // Converts camera coordinates to normalize programs (so quarters between 0 and 1)

out vec3 Normal;
out vec3 FragmentPosition;

void main()
{
  gl_Position = projection * view * model * vec4(position, 1.0f);
  FragmentPosition = vec3(model * vec4(position, 1.0f));
  Normal = mat3(transpose(inverse(model))) * normal;
}
