/**
 * Object Handler - A 3D Model Viewer for .obj file extension.
 * Copyright (C) 2019  Gabriel Moraes de Oliveira <biel94moraes@msn.com>
 */



#ifndef UTIL_H
#define UTIL_H

#include "objecthandlerpch.h"



class Util
{
  public:
    static std::string getFileContent(const std::string filePath);
};

#endif
