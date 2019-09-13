/**
 * Object Handler - A 3D Model Viewer.
 * Copyright (C) 2019  Gabriel Moraes de Oliveira <biel94moraes@msn.com>
 */



#pragma once

#include <GL/glew.h>
#include "graphic_mesh.h"



class Model
{
  public:
    Model() {}

    // Expects a filepath to a 3D model
    Model(GLchar *path);



    // Draws the model, and thus all its meshes
    void draw(GraphicShader graphicShader);

    static GLint getTextureFromFile(const char *path, std::string directory);



  private:
    // Model Data
    std::vector<Mesh> meshes;
    std::string directory;
    std::vector<Texture> loadedTextures; // Stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once

    // For prints
    uint64_t totalNumMeshes;
    uint64_t totalNumVertices;
    uint64_t totalNumTriangles;
    uint32_t totalNumTextures;



    // Loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector
    void loadModel(std::string path);

    // Processes recursively each individual mesh located at the node and repeats this process on its children nodes (if any).
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);

    // Checks all material textures of a given type and loads the textures if they're not loaded yet.
    // The required info is returned as a Texture struct.
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};
