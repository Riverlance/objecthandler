#version 330 core

layout(location = 0) in vec3 position;

uniform mat4 model; // Converts local object coordinates to camera coordinates
uniform mat4 view; // Converts quarter the normalized coordinates to window
uniform mat4 projection; // Converts camera coordinates to normalize programs (so quarters between 0 and 1)

void main()
{
  gl_Position = projection * view * model * vec4(position, 1.0f);
}
