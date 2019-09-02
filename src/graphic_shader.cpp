/**
 * Object Handler - A 3D Model Viewer for .obj file extension.
 * Copyright (C) 2019  Gabriel Moraes de Oliveira <biel94moraes@msn.com>
 */



#include "objecthandlerpch.h"

#include "graphic_shader.h"
#include "util.h"



const int infoLogSize = 512;

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
    std::cerr << "> Failed to load vertex shader.\n\tGLEW error: " << infoLog << std::endl;
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



void GraphicShader::use()
{
  glUseProgram(program);
}
