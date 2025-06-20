#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"

static unsigned int TextureFromFile(const char* path, const std::string& directory);

class Model
{
private:
	std::string m_Directory;
	std::vector<MeshTexture> m_LoadedTextures;

	void loadModel(const std::string& path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<MeshTexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName);
public:
	std::vector<Mesh> m_Meshes;

	Model(const std::string& path)
	{
		loadModel(path);
	}
	void Draw(Shader& shader);
};
