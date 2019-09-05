/**
 * Object Handler - A 3D Model Viewer for .obj file extension.
 * Copyright (C) 2019  Gabriel Moraes de Oliveira <biel94moraes@msn.com>
 */



// Collection of functions especially designed to be used on ranges of elements
#include <algorithm>

// Set of functions to compute common mathematical operations and transformations (e.g., ceil, floor, abs, round, pow, sqrt, sin, cos, tan, acos, asin, atan, cosh, sinh, tanh, acosh, asinh, atanh, ...)
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include <cmath>

// Set of integral type aliases with specific width requirements
#include <cstdint>

// Sequence containers that allow constant time insert and erase operations anywhere within the sequence
#include <forward_list>

// Parametric manipulators (e.g., get_time, put_time)
#include <iomanip>

// Standard input/output stream objects (also std::cout, std::endl, ...)
#include <iostream>

// Sequence containers that allow constant time insert and erase operations anywhere within the sequence, and iteration in both directions
#include <list>

// Associative containers that store elements formed by a combination of a key value and a mapped value, following a specific order
#include <map>

// Critical sections for preventing other threads with the same protection from executing concurrently and access the same memory locations
#include <mutex>

// Input/output stream class to operate on files (e.g., std::string)
#include <fstream>

// String stream classes (e.g., std::ostringstream)
#include <sstream>

// Introduces string types, character traits and a set of converting functions
#include <string>

// Thread class and the this_thread namespace
#include <thread>

// Associative containers that store elements formed by the combination of a key value and a mapped value, and which allows for fast retrieval of individual elements based on their keys
#include <unordered_map>

// Sequence containers representing arrays that can change in size
#include <vector>

// GLM mathematics
#define GLM_FORCE_CTOR_INIT // Initialize variables like glm::mat4 automatically, as the old GLM version
/*
  - Without GLM_FORCE_CTOR_INIT (GLM deprecated variable initializations, so you need to declare it):
  glm::mat4 transform = glm::mat4(1.0, 0.0, 0.0, 0.0,
                                  0.0, 1.0, 0.0, 0.0,
                                  0.0, 0.0, 1.0, 0.0,
                                  0.0, 0.0, 0.0, 1.0);

  - With GLM_FORCE_CTOR_INIT (force variable initializations, as old GLM versions):
  glm::mat4 transform;

  Both are the same.
*/
#include <glm/glm.hpp> // Features that implement in C++ the GLSL specification as closely as possible
#pragma warning(push)
#pragma warning(disable:4127) // conditional expression is constant
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#pragma warning(pop)
#pragma warning(push)
#pragma warning(disable:4201) // nonstandard extension used: nameless struct/union
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr, quaternion
#include <glm/gtx/string_cast.hpp>
#pragma warning(pop)
// Sample
/*
  glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.f);
  glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
  View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
  View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
  glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
  return Projection * View * Model;
*/

// SOIL
#include <SOIL2.h>

// Assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// To do
// Light-weight C++ XML processing library
//#include <pugixml.hpp>



#ifdef _WIN32
// String comparing
#define strcasecmp _stricmp
#define strncasecmp _strnicmp
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
