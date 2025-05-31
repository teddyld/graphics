#include "Mesh.h"

void Mesh::setupMesh()
{
	m_VAO = std::make_unique<VertexArray>();
	m_VBO = std::make_unique<VertexBuffer>(&m_Vertices[0], m_Vertices.size() * sizeof(MeshVertex), GL_STATIC_DRAW);
	m_EBO = std::make_unique<IndexBuffer>(&m_Indices[0], m_Indices.size());

	VertexBufferLayout layout;
	layout.Push(GL_FLOAT, 3, GL_FALSE);
	layout.Push(GL_FLOAT, 3, GL_FALSE);
	layout.Push(GL_FLOAT, 2, GL_FALSE);
	layout.Push(GL_FLOAT, 3, GL_FALSE);
	layout.Push(GL_FLOAT, 3, GL_FALSE);
	layout.Push(GL_INT, 4, GL_FALSE);
	layout.Push(GL_FLOAT, 4, GL_FALSE);
	m_VAO->AddBuffer(*m_VBO, layout);
}

Mesh::Mesh(std::vector<MeshVertex> vertices, std::vector<unsigned int> indices, std::vector<MeshTexture> textures)
	: m_Vertices(vertices), m_Indices(indices), m_Textures(textures)
{
	setupMesh();
}

void Mesh::Draw(Shader& shader)
{
	Renderer renderer;

	shader.Bind();
	m_VAO->Bind();

	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	for (unsigned int i = 0; i < m_Textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);

		std::string number;
		std::string name = m_Textures[i].type;

		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = std::to_string(specularNr++);

		shader.SetUniform1i(("material." + name + number).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, m_Textures[i].id);
	}

	renderer.Draw(*m_VAO, *m_EBO, shader);

	glActiveTexture(GL_TEXTURE0);
}