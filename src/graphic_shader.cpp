/**
 * Object Handler - A 3D Model Viewer for .obj file extension.
 * Copyright (C) 2019  Gabriel Moraes de Oliveira <biel94moraes@msn.com>
 */



#include "objecthandlerpch.h"

#include "graphic_shader.h"



bool GraphicShader::load(const GLchar* vertexPath, const GLchar* fragmentPath)
{
  /// Retrieve the vertex/fragment source code from filePath

  std::string vertexCode;
  std::string fragmentCode;
  std::ifstream vertexShaderFile;
  std::ifstream fragmentShaderFile;

  // Ensure ifstream objects can throw exceptions
  vertexShaderFile.exceptions(std::ifstream::badbit);
  fragmentShaderFile.exceptions(std::ifstream::badbit);

  try
  {
    // Open files
    vertexShaderFile.open(vertexPath);
    fragmentShaderFile.open(fragmentPath);

    if (!vertexShaderFile.is_open() || !fragmentShaderFile.is_open())
    {
      std::cout << "> Failed to read shader files.\nFile not found or has no access to read." << std::endl;
      return false;
    }

    // Read file's buffer contents into streams
    std::stringstream vertexShaderStream, fragmentShaderStream;
    vertexShaderStream << vertexShaderFile.rdbuf();
    fragmentShaderStream << fragmentShaderFile.rdbuf();

    // Close file handlers
    vertexShaderFile.close();
    fragmentShaderFile.close();

    // Convert stream into string
    vertexCode = vertexShaderStream.str();
    fragmentCode = fragmentShaderStream.str();

    std::cout << "> Shader files loaded successfully." << std::endl;
  }
  catch (std::ifstream::failure error)
  {
    std::cout << "> Failed to read shader files.\n" << error.what() << std::endl;
    return false;
  }



  /// Compile shaders

  const GLchar* vertexShaderCode = vertexCode.c_str();
  const GLchar* fragmentShaderCode = fragmentCode.c_str();

  // Print code
  // std::cout << vertexShaderCode << std::endl;
  // std::cout << fragmentShaderCode << std::endl;

  GLuint vertex, fragment;
  GLint success;
  const int infoLogSize = 512;
  GLchar infoLog[infoLogSize];



  // Vertex shader
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vertexShaderCode, NULL);
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
  glShaderSource(fragment, 1, &fragmentShaderCode, NULL);
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
