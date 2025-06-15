#include "TestBatchRendering.h"

namespace test {
	TestBatchRendering::TestBatchRendering()
		: m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))), m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f))
	{
		float vertices[] = {
			120.0f, 120.0f, 0.0f, 0.0f, 0.0f,
			220.0f, 120.0f, 1.0f, 0.0f, 0.0f,
			220.0f, 220.0f, 1.0f, 1.0f, 0.0f,
			120.0f, 220.0f, 0.0f, 1.0f, 0.0f,

			320.0f, 120.0f, 0.0f, 0.0f, 1.0f,
			420.0f, 120.0f, 1.0f, 0.0f, 1.0f,
			420.0f, 220.0f, 1.0f, 1.0f, 1.0f,
			320.0f, 220.0f, 0.0f, 1.0f, 1.0f,
		};

		unsigned int indices[] = {
			0, 1, 2, 2, 3, 0,
			4, 5, 6, 6, 7, 4
		};

		m_VAO = std::make_unique<VertexArray>();
		m_EBO = std::make_unique<IndexBuffer>(indices, 12);

		m_VBO = std::make_unique<VertexBuffer>(vertices, 8 * 9 * sizeof(float), GL_STATIC_DRAW);

		VertexBufferLayout layout;
		layout.Push(GL_FLOAT, 2, GL_FALSE);
		layout.Push(GL_FLOAT, 2, GL_FALSE);
		layout.Push(GL_FLOAT, 1, GL_FALSE);
		m_VAO->AddBuffer(*m_VBO, layout);

		m_TextureBear = std::make_unique<Texture>("res/textures/bear.png");
		m_TextureMaple = std::make_unique<Texture>("res/textures/maple.png");

		m_Shader = std::make_unique<Shader>("res/shaders/Texture16.shader");
		m_Shader->Bind();

		int samplers[2] = { 0, 1 };

		m_Shader->SetUniform1iv("u_Textures", 2, samplers);

		glm::mat4 mvp = m_Proj * m_View;
		m_Shader->SetUniformMat4f("u_MVP", mvp);

		m_VAO->Unbind();
		m_VBO->Unbind();
		m_EBO->Unbind();
		m_Shader->Unbind();
	}

	void TestBatchRendering::OnRender()
	{
		Renderer renderer;

		m_TextureBear->Bind(0);
		m_TextureMaple->Bind(1);

		renderer.Draw(*m_VAO, *m_EBO, *m_Shader);
	}
}