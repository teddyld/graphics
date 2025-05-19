#include "Water.h"

glm::mat4 waterModel = glm::scale(glm::mat4(1.0f), glm::vec3(20.0f, 1.0f, 1.0f));

Water::Water()
{
	float vertices[] = {
		0.0f, 0.0f, 0.5f, 0.0f, 0.0f,
		112.0f, 0.0f, 0.5f, 10.0f, 0.0f,
		112.0f, 96.0f, 0.5f, 10.0f, 1.0f,
		0.0f, 96.0f, 0.5f, 0.0f, 1.0f
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

	std::map<GLenum, GLint> options = {
		{ GL_TEXTURE_MIN_FILTER, GL_LINEAR },
		{ GL_TEXTURE_MAG_FILTER, GL_LINEAR },
		{ GL_TEXTURE_WRAP_S, GL_REPEAT },
		{ GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE }
	};

	m_Texture = std::make_unique<Texture>("res/textures/magic_cliffs/environment/sea.png", options);

	m_Shader = std::make_unique<Shader>("res/shaders/Water.shader");
	m_Shader->Bind();

	m_Shader->SetUniform1i("u_Texture", 0);
}

void Water::OnRender(glm::mat4 view, glm::mat4 projection)
{
	Renderer renderer;

	m_Texture->Bind(0);

	glm::mat4 mvp = projection * view * waterModel;

	m_Shader->Bind();
	m_Shader->SetUniformMat4f("u_MVP", mvp);

	renderer.Draw(*m_VAO, *m_EBO, *m_Shader);
}