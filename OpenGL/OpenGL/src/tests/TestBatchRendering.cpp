#include "TestBatchRendering.h"

namespace test {
	TestBatchRendering::TestBatchRendering()
		: m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))), m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f))
	{
		float positions[] = {
			120.0f, 120.0f,
			220.0f, 120.0f,
			220.0f, 220.0f,
			120.0f, 220.0f,

			320.0f, 120.0f,
			420.0f, 120.0f,
			420.0f, 220.0f,
			320.0f, 220.0f,
		};

		unsigned int indices[] = {
			0, 1, 2, 2, 3, 0,
			4, 5, 6, 6, 7, 4
		};

		m_VAO = std::make_unique<VertexArray>();
		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 12);

		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 8 * 2 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push(GL_FLOAT, 2, GL_FALSE);
		m_VAO->AddBuffer(*m_VertexBuffer, layout);

		m_Shader = std::make_unique<Shader>("res/shaders/BasicColor.shader");
		m_Shader->Bind();
		m_Shader->SetUniform4f("u_Color", 0.4f, 0.8f, 0.1f, 1.0f);

		glm::mat4 mvp = m_Proj * m_View;
		m_Shader->SetUniformMat4f("u_MVP", mvp);

		m_VAO->Unbind();
		m_VertexBuffer->UnBind();
		m_IndexBuffer->UnBind();
		m_Shader->Unbind();
	}

	void TestBatchRendering::OnRender()
	{
		Renderer renderer;
		renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
	}

	void TestBatchRendering::OnImGuiRender()
	{
	}
}