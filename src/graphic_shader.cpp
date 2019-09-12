/**
 * Object Handler - A 3D Model Viewer.
 * Copyright (C) 2019  Gabriel Moraes de Oliveira <biel94moraes@msn.com>
 */



#include "objecthandlerpch.h"

#include "graphic_shader.h"
#include "util.h"



const int infoLogSize = 512;



GraphicShader::GraphicShader(std::vector<std::pair<GLenum, const GLchar*>> shaders)
{
  std::vector<GLuint> shadersToAttach;

  // Load shaders
  for (auto it = shaders.rbegin(), end = shaders.rend(); it != end; ++it)
  {
    GLuint shader = loadShader(it->first, it->second);
    if (shader == 0)
      return;
    shadersToAttach.emplace_back(shader);
  }

  // Load program
  loadProgram();

  // Attach shaders
  for (auto it = shadersToAttach.rbegin(), end = shadersToAttach.rend(); it != end; ++it)
    attachShader(*it);

  // Shader program
  if (!linkProgram())
    return;
}



GLuint GraphicShader::loadShader(GLenum shaderType, const GLchar* path)
{
  std::string _fileContent = Util::getFileContent(path);
  if (_fileContent == "")
    return 0; // Error
  const GLchar* fileContent = _fileContent.c_str();
  const GLint fileContentLength = (GLint)_fileContent.size();

  GLuint shader;
  GLint success;
  GLchar infoLog[infoLogSize];

  shader = glCreateShader(shaderType);
  glShaderSource(shader, 1, &fileContent, &fileContentLength);
  glCompileShader(shader);
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(shader, infoLogSize, NULL, infoLog);
    std::cerr << "> Failed to load shader of path '" << path << "'.\n\tGLEW error: " << infoLog << std::endl;
    return 0; // Error
  }

  return shader;
}

void GraphicShader::loadProgram()
{
  program = glCreateProgram();
}

bool GraphicShader::attachShader(GLuint shader)
{
  if (!program)
  {
    std::cerr << "> Failed to attach shader.\n\tProgram is not loaded." << std::endl;
    return false;
  }
  // Attach shader
  glAttachShader(program, shader);

  // Delete the shader as they are attached into program and are not longer necessary
  glDeleteShader(shader);

  return true;
}

bool GraphicShader::linkProgram()
{
  GLint success;
  glLinkProgram(program);
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success)
  {
    GLchar infoLog[infoLogSize];
    glGetProgramInfoLog(program, infoLogSize, NULL, infoLog);
    std::cerr << "> Failed to link shader program.\n\tGLEW error: " << infoLog << std::endl;
    return false;
  }

  return true;
}



void GraphicShader::useProgram()
{
  glUseProgram(program);
}
