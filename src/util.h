/**
 * Object Handler - A 3D Model Viewer.
 * Copyright (C) 2019  Gabriel Moraes de Oliveira <biel94moraes@msn.com>
 */



#pragma once

#include "const.h"



class Util
{
  public:
    static std::string getFileContent(const std::string filePath);
    static void setTheme(Theme_t theme = THEME_NONE);
};
