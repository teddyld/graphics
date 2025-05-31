#pragma once

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Renderer.h"

#define MAX_BONE_INFLUENCE 4

struct MeshVertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
	// Bone indexes which will influence this vertex
	int m_BoneIDs[MAX_BONE_INFLUENCE];
	// Weights from each bone
	float m_Weights[MAX_BONE_INFLUENCE];
};

struct MeshTexture {
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh
{
private:
	std::unique_ptr<VertexArray> m_VAO;
	std::unique_ptr<VertexBuffer> m_VBO;
	std::unique_ptr<IndexBuffer> m_EBO;

	void setupMesh();
public:
	std::vector<MeshVertex>  m_Vertices;
	std::vector<unsigned int> m_Indices;
	std::vector<MeshTexture> m_Textures;

	Mesh(std::vector<MeshVertex> vertices, std::vector<unsigned int> indices, std::vector<MeshTexture> textures);
	void Draw(Shader& shader);
};