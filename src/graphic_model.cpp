/**
 * Object Handler - A 3D Model Viewer.
 * Copyright (C) 2019  Gabriel Moraes de Oliveira <biel94moraes@msn.com>
 */



#include "objecthandlerpch.h"

#include "graphic_model.h"




Model::Model(GLchar *path) :
  totalNumMeshes(0ULL),
  totalNumVertices(0ULL),
  totalNumTriangles(0ULL),
  totalNumTextures(0ULL)
{
  loadModel(path);
}



void Model::draw(GraphicShader graphicShader)
{
  for (GLuint i = 0; i < meshes.size(); i++)
    meshes[i].draw(graphicShader);
}

GLint Model::getTextureFromFile(const char *path, std::string directory) // static
{
  //Generate texture ID and load texture data
  std::string filename = std::string(path);
  filename = directory + '/' + filename;
  GLuint textureID;
  glGenTextures(1, &textureID);

  int width, height;

  unsigned char *image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);

  // Assign texture to ID
  glBindTexture(GL_TEXTURE_2D, textureID);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
  glGenerateMipmap(GL_TEXTURE_2D);

  // Parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, 0);
  SOIL_free_image_data(image);

  return textureID;
}



void Model::loadModel(std::string path)
{
  // Read file via ASSIMP
  Assimp::Importer importer;
  const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

  // Check for errors
  if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
  {
    std::cout << "> Failed to load model.\n\tASSIMP Error: " << importer.GetErrorString() << std::endl;
    return;
  }

  // Retrieve the directory path of the filepath
  directory = path.substr(0, path.find_last_of('/'));

  // Process ASSIMP's root node recursively
  processNode(scene->mRootNode, scene);

  // Print
  std::cout << std::endl;
  std::cout << "> Total:" << std::endl;
  std::cout << "\t" << unsigned(totalNumMeshes) << " mesh" << (totalNumMeshes > 1 ? "es" : "") << std::endl;
  std::cout << "\t" << unsigned(totalNumVertices) << " vert" << (totalNumVertices > 1 ? "ices" : "ex") << std::endl;
  std::cout << "\t" << unsigned(totalNumTriangles) << " triangle" << (totalNumTriangles > 1 ? "s" : "") << std::endl;
  std::cout << "\t" << unsigned(totalNumTextures) << " texture" << (totalNumTextures > 1 ? "s" : "") << std::endl;
  std::cout << std::endl;
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
  std::cout << "> Mesh node found with " << unsigned(node->mNumMeshes) << " mesh" << (node->mNumMeshes > 1 ? "es" : "") << " and " << unsigned(node->mNumChildren) << " child" << (node->mNumChildren > 1 ? "ren" : "") << ":" << std::endl;
  totalNumMeshes += node->mNumMeshes; // For print

  // Process each mesh located at the current node
  for (GLuint i = 0; i < node->mNumMeshes; i++)
  {
    // The node object only contains indices to index the actual objects in the scene
    // The scene contains all the data, node is just to keep stuff organized (like relations between nodes)
    aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

    meshes.push_back(processMesh(mesh, scene));
  }

  // After we've processed all of the meshes (if any) we then recursively process each of the children nodes
  for (GLuint i = 0; i < node->mNumChildren; i++)
  {
    std::cout << "Children mesh " << (i + 1) << ":" << std::endl;

    processNode(node->mChildren[i], scene);
  }
  std::cout << std::endl;
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
  // Data to fill
  std::vector<Vertex> vertices;
  std::vector<GLuint> indices;
  std::vector<Texture> textures;

  std::cout << "\t\t> " << unsigned(mesh->mNumVertices) << " vert" << (mesh->mNumVertices > 1 ? "ices" : "ex") << std::endl;
  std::cout << "\t\t> " << unsigned(mesh->mNumFaces) << " triangle" << (mesh->mNumFaces > 1 ? "s" : "") << std::endl;
  totalNumVertices += mesh->mNumVertices; // For print
  totalNumTriangles += mesh->mNumFaces; // For print (since aiProcess_Triangulate is enabled, all faces are triangles)

  // Walk through each of the mesh's vertices
  for (GLuint i = 0; i < mesh->mNumVertices; i++)
  {
    Vertex vertex;
    glm::vec3 vector; // We declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.

    // Positions
    vector.x = mesh->mVertices[i].x;
    vector.y = mesh->mVertices[i].y;
    vector.z = mesh->mVertices[i].z;
    vertex.Position = vector;

    // Normals
    vector.x = mesh->mNormals[i].x;
    vector.y = mesh->mNormals[i].y;
    vector.z = mesh->mNormals[i].z;
    vertex.Normal = vector;

    // Texture Coordinates
    if (mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
    {
      glm::vec2 vec;
      // A vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
      // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
      vec.x = mesh->mTextureCoords[0][i].x;
      vec.y = mesh->mTextureCoords[0][i].y;
      vertex.TextureCoordinates = vec;
    }
    else
      vertex.TextureCoordinates = glm::vec2(0.0f, 0.0f);

    vertices.push_back(vertex);
  }

  // Now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
  for (GLuint i = 0; i < mesh->mNumFaces; i++)
  {
    aiFace face = mesh->mFaces[i];
    // Retrieve all indices of the face and store them in the indices vector
    for (GLuint j = 0; j < face.mNumIndices; j++)
      indices.push_back(face.mIndices[j]);
  }

  // Process materials
  if (mesh->mMaterialIndex >= 0)
  {
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    // We assume a convention for sampler names in the shaders. Each diffuse texture should be named
    // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
    // Same applies to other texture as the following list summarizes:
    // Diffuse: texture_diffuseN
    // Specular: texture_specularN
    // Normal: texture_normalN

    // Texture 1. Diffuse maps
    std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    // Texture 2. Specular maps
    std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
  }

  // Return a mesh object created from the extracted mesh data
  return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
{
  std::vector<Texture> textures;

  std::cout << "\t\t> " << unsigned(mat->GetTextureCount(type)) << " texture" << (mat->GetTextureCount(type) > 1 ? "s" : "") << " (" << typeName << ")" << std::endl;
  totalNumTextures += mat->GetTextureCount(type); // For print

  for (GLuint i = 0; i < mat->GetTextureCount(type); i++)
  {
    aiString str;
    mat->GetTexture(type, i, &str);

    // Check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
    GLboolean skip = false;

    for (GLuint j = 0; j < loadedTextures.size(); j++)
    {
      if (loadedTextures[j].path == str)
      {
        textures.push_back(loadedTextures[j]);
        skip = true; // A texture with the same filepath has already been loaded, continue to next one. (optimization)

        break;
      }
    }

    // If texture hasn't been loaded already, load it
    if (!skip)
    {
      Texture texture;
      texture.id = getTextureFromFile(str.C_Str(), directory);
      texture.type = typeName;
      texture.path = str;
      textures.push_back(texture);

      loadedTextures.push_back(texture); // Store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
    }
  }

  return textures;
}
