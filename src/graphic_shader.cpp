/**
 * Object Handler - A 3D Model Viewer for .obj file extension.
 * Copyright (C) 2019  Gabriel Moraes de Oliveira <biel94moraes@msn.com>
 */



#include "objecthandlerpch.h"

#include "graphic_shader.h"
#include "util.h"



bool GraphicShader::load(const GLchar* vertexPath, const GLchar* fragmentPath)
{
  /// Retrieve the vertex/fragment source code from filePath

  // Vertex
  std::string _vertexShaderCode = Util::getFileContent(vertexPath);
  if (_vertexShaderCode == "")
    return false;
  const GLchar* vertexShaderCode = _vertexShaderCode.c_str();
  const GLint vertexShaderCodeLength = (GLint)_vertexShaderCode.size();
  // Fragment
  std::string _fragmentShaderCode = Util::getFileContent(fragmentPath);
  if (_fragmentShaderCode == "")
    return false;
  const GLchar* fragmentShaderCode = _fragmentShaderCode.c_str();
  const GLint fragmentShaderCodeLength = (GLint)_fragmentShaderCode.size();
  


  /// Compile shaders
  
  GLuint vertex, fragment;
  GLint success;
  const int infoLogSize = 512;
  GLchar infoLog[infoLogSize];

  // Vertex shader
  
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vertexShaderCode, &vertexShaderCodeLength);
  glCompileShader(vertex);
  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(vertex, infoLogSize, NULL, infoLog);
    std::cout << "> Failed to load vertex shader.\nGLEW error: " << infoLog << std::endl;
    return false;
  }



  // Fragment shader
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fragmentShaderCode, &fragmentShaderCodeLength);
  glCompileShader(fragment);
  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(fragment, infoLogSize, NULL, infoLog);
    std::cout << "> Failed to load fragment shader.\nGLEW error: " << infoLog << std::endl;
    return false;
  }



  // Shader program
  program = glCreateProgram();
  glAttachShader(program, vertex);
  glAttachShader(program, fragment);
  glLinkProgram(program);
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success)
  {
    glGetProgramInfoLog(program, infoLogSize, NULL, infoLog);
    std::cout << "> Failed to load shader program.\nGLEW error: " << infoLog << std::endl;
    return false;
  }



  // Delete the shaders as they are linked into our program now and are not longer necessary
  glDeleteShader(vertex);
  glDeleteShader(fragment);

  return true;
}

void GraphicShader::use()
{
  glUseProgram(program);
}
