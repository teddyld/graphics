#include "Landscape.h"

Landscape::Landscape()
{
	float vertices[] = {
		0.0f, 0.0f, 0.2f, 0.0f, 0.0f,
		512.0f, 0.0f, 0.2f, 0.5f, 0.0f,
		512.0f, 302.0f, 0.2f, 0.5f, 1.0f,
		0.0f, 302.0f, 0.2f, 0.0f, 1.0f,
	};

	unsigned int indices[] = {
		0, 1, 2, 2, 3, 0
	};

	m_VAO = std::make_unique<VertexArray>();
	m_EBO = std::make_unique<IndexBuffer>(indices, 6);
	m_VBO = std::make_unique<VertexBuffer>(vertices, 4 * 5 * sizeof(float), GL_STATIC_DRAW);

	VertexBufferLayout layout;
	layout.Push(GL_FLOAT, 3, GL_FALSE);
	layout.Push(GL_FLOAT, 2, GL_FALSE);
	m_VAO->AddBuffer(*m_VBO, layout);

	m_Texture = std::make_unique<Texture>("res/textures/magic_cliffs/environment/magic-cliffs-preview-detail.png");

	m_Shader = std::make_unique<Shader>("res/shaders/Texture1.shader");
	m_Shader->Bind();

	m_Shader->SetUniform1i("u_Texture", 0);
	m_Shader->Unbind();

	m_VAO->Unbind();
	m_VBO->Unbind();
	m_EBO->Unbind();
}

void Landscape::OnRender(glm::mat4 view, glm::mat4 projection)
{
	Renderer renderer;

	m_Texture->Bind(0);

	glm::mat4 mvp = projection * view;

	m_Shader->Bind();
	m_Shader->SetUniformMat4f("u_MVP", mvp);

	renderer.Draw(*m_VAO, *m_EBO, *m_Shader);
}