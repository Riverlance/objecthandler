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

void Util::setTheme(Theme_t theme /*= THEME_NONE*/) // static
{
  // Next theme
  if (theme == THEME_NONE)
    theme = (Theme_t)(((int)APP_THEME + 1) % (THEME_LAST + 1));

  switch (theme)
  {
  case THEME_LIGHT:
    APP_THEME = theme;
    // Clear color
    THEME_CLEARCOLOR_R = 0.7f;
    THEME_CLEARCOLOR_G = 0.7f;
    THEME_CLEARCOLOR_B = 0.7f;
    THEME_CLEARCOLOR_A = 1.0f;
    break;

  case THEME_DARK:
    APP_THEME = theme;
    // Clear color
    THEME_CLEARCOLOR_R = 0.1171875f;
    THEME_CLEARCOLOR_G = 0.1171875f;
    THEME_CLEARCOLOR_B = 0.1171875f;
    THEME_CLEARCOLOR_A = 1.0f;
    break;

  default:
    break;
  }
}
