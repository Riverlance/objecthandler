/**
 * Object Handler - A 3D Model Viewer.
 * Copyright (C) 2019  Gabriel Moraes de Oliveira <biel94moraes@msn.com>
 */



#include "objecthandlerpch.h"

#include "util.h"



std::string Util::getFileContent(const std::string filePath) // static
{
  std::string output;
  try
  {
    std::ifstream file(filePath);

    if (!file.is_open())
    {
      std::cerr << "> Failed to open file from path '" << filePath << "'." << std::endl;
      return output;
    }

    // Ensure ifstream objects can throw exceptions
    file.exceptions(std::ifstream::badbit);

    std::string line;
    while (getline(file, line))
      output += line + "\n";

    // Close file handler
    file.close();
  }
  catch (std::ifstream::failure error)
  {
    std::cerr << "> Failed to read shader files.\n\t" << error.what() << std::endl;
    return output;
  }

  return output;
}
