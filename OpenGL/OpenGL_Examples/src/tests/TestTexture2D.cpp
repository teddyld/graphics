#include "TestTexture2D.h"

namespace test {
	TestTexture2D::TestTexture2D()
		: m_TranslationA(200, 200, 0), m_TranslationB(400, 200, 0), m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))), m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f))
	{
		float positions[] = {
			-50.0f, -50.0f, 0.0f, 0.0f,	// 0
			50.0f, -50.0f, 1.0f, 0.0f,	// 1
			50.0f, 50.0f, 1.0f, 1.0f,	// 2
			-50.0f, 50.0f, 0.0f, 1.0f,	// 3
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		m_VAO = std::make_unique<VertexArray>();
		m_EBO = std::make_unique<IndexBuffer>(indices, 6);

		m_VBO = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float), GL_STATIC_DRAW);

		VertexBufferLayout layout;
		layout.Push(GL_FLOAT, 2, GL_FALSE);
		layout.Push(GL_FLOAT, 2, GL_FALSE);
		m_VAO->AddBuffer(*m_VBO, layout);

		m_Shader = std::make_unique<Shader>("res/shaders/Texture.shader");
		m_Shader->Bind();

		m_Texture = std::make_unique<Texture>("res/textures/bear.png");
		m_Shader->SetUniform1i("u_Texture", 0);

		m_VAO->Unbind();
		m_VBO->Unbind();
		m_EBO->Unbind();
		m_Shader->Unbind();
	}

	void TestTexture2D::OnRender()
	{
		Renderer renderer;

		m_Texture->Bind();
		m_Shader->Bind();

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
			glm::mat4 mvp = m_Proj * m_View * model;
			m_Shader->SetUniformMat4f("u_MVP", mvp);

			renderer.Draw(*m_VAO, *m_EBO, *m_Shader);
		}

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
			glm::mat4 mvp = m_Proj * m_View * model;
			m_Shader->SetUniformMat4f("u_MVP", mvp);

			renderer.Draw(*m_VAO, *m_EBO, *m_Shader);
		}
	}

	void TestTexture2D::OnImGuiRender()
	{
		ImGui::SliderFloat3("Model translation A", &m_TranslationA.x, 0.0f, 960.0f);
		ImGui::SliderFloat3("Model translation B", &m_TranslationB.x, 0.0f, 960.0f);
	}
}