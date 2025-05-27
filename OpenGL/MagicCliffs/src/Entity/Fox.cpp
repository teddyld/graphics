#include "Fox.h"
#include <iostream>

glm::mat4 foxModel = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 145.0f, 0.0f));

Fox::Fox()
	: Entity(foxModel, 100.0f, glm::vec3(1.0f, 1.0f, 1.0f)), m_TextureID(0.0f)
{
	unsigned int indices[] = {
		0, 1, 2, 2, 3, 0,
	};

	m_VAO = std::make_unique<VertexArray>();
	m_EBO = std::make_unique<IndexBuffer>(indices, 6);
	m_VBO = std::make_unique<VertexBuffer>(nullptr, 4 * sizeof(EntityVertex), GL_DYNAMIC_DRAW);

	VertexBufferLayout layout;
	layout.Push(GL_FLOAT, 3, GL_FALSE);
	layout.Push(GL_FLOAT, 2, GL_FALSE);
	layout.Push(GL_FLOAT, 1, GL_FALSE);
	m_VAO->AddBuffer(*m_VBO, layout);

	for (int i = 0; i < 8; i++)
	{
		std::string path = "res/textures/magic_cliffs/fox_sword/fox-sword" + std::to_string(i + 1) + ".png";
		std::unique_ptr<Texture> foxTexture = std::make_unique<Texture>(path);
		m_Textures.push_back(std::move(foxTexture));
	}

	m_Shader = std::make_unique<Shader>("res/shaders/Texture16.shader");
	m_Shader->Bind();

	int samplers[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	m_Shader->SetUniform1iv("u_Textures", 8, samplers);
}

void Fox::OnUpdate(float deltaTime)
{
	// Animate texture
	m_TextureID = m_TextureID + 0.07f;
	if (m_TextureID > 7.0f)
	{
		m_TextureID = 0.0f;
	}

	// Update position and loop animation
	m_Position.x = (m_Position.x + m_Speed * deltaTime);
	if (m_Position.x > 520.0f)
	{
		m_Position.x = -50.0f;
	}
}

void Fox::OnRender(glm::mat4 view, glm::mat4 projection)
{
	Renderer renderer;

	for (unsigned int i = 0; i < m_Textures.size(); i++)
	{
		m_Textures[i]->Bind(i);
	}

	glm::mat4 modelPosition = glm::translate(m_Model, glm::vec3(m_Position.x, 0.0f, 0.0f));

	glm::mat4 mvp = projection * view * modelPosition;

	m_Shader->Bind();
	m_Shader->SetUniformMat4f("u_MVP", mvp);

	float vertices[] = {
		0.0f, 0.0f, 1.0f, 0.0f, 0.0f, m_TextureID,
		80.0f, 0.0f, 1.0f, 1.0f, 0.0f, m_TextureID,
		80.0f, 48.0f, 1.0f, 1.0f, 1.0f, m_TextureID,
		0.0f, 48.0f, 1.0f, 0.0f, 1.0f, m_TextureID,
	};

	m_VBO->UpdateBufferSubData(0, 4 * sizeof(EntityVertex), vertices);

	renderer.Draw(*m_VAO, *m_EBO, *m_Shader);
}