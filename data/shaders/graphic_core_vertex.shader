#version 330 core

layout (location = 0) in vec3 position;
layout(location = 1) in vec2 textureCoordinate;

out vec2 ourTextureCoordinate;

uniform mat4 model; // Converts local object coordinates to camera coordinates
uniform mat4 view; // Converts quarter the normalized coordinates to window
uniform mat4 projection; // Converts camera coordinates to normalize programs (so quarters between 0 and 1)

void main()
{
  gl_Position = projection * view * model * vec4(position, 1.0f);
  ourTextureCoordinate = vec2(textureCoordinate.x, 1.0f - textureCoordinate.y);
}
