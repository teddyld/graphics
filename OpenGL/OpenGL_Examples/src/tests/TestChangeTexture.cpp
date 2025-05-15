#include "TestChangeTexture.h"

namespace test {
	TestChangeTexture::TestChangeTexture()
		: m_View(glm::mat4(1.0f)), m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)), m_TextureID(0)
	{
		unsigned int indices[] = {
			0, 1, 2, 2, 3, 0
		};

		m_VAO = std::make_unique<VertexArray>();
		m_EBO = std::make_unique<IndexBuffer>(indices, 6);
		m_VBO = std::make_unique<VertexBuffer>(nullptr, 4 * sizeof(Vertex2D), GL_DYNAMIC_DRAW);

		VertexBufferLayout layout;
		layout.Push(GL_FLOAT, 2, GL_FALSE);
		layout.Push(GL_FLOAT, 2, GL_FALSE);
		layout.Push(GL_FLOAT, 1, GL_FALSE);
		m_VAO->AddBuffer(*m_VBO, layout);

		std::unique_ptr<Texture> grassBottom = std::make_unique<Texture>("res/textures/minecraft/grass_bottom.jpg");
		m_Textures.push_back(std::move(grassBottom));

		std::unique_ptr<Texture> grassTop = std::make_unique<Texture>("res/textures/minecraft/grass_top.jpg");
		m_Textures.push_back(std::move(grassTop));

		std::unique_ptr<Texture> grassSide = std::make_unique<Texture>("res/textures/minecraft/grass_side.jpg");
		m_Textures.push_back(std::move(grassSide));

		m_Shader = std::make_unique<Shader>("res/shaders/Texture16.shader");
		m_Shader->Bind();

		int samplers[3] = { 0, 1, 2 };
		m_Shader->SetUniform1iv("u_Textures", 3, samplers);

		glm::mat4 mvp = m_Proj * m_View;
		m_Shader->SetUniformMat4f("u_MVP", mvp);
	}

	void TestChangeTexture::OnUpdate(GLFWwindow* window, float deltaTime, Camera* camera)
	{
		float currentFrame = (float)glfwGetTime();
	}

	void TestChangeTexture::OnRender()
	{
		Renderer renderer;

		for (unsigned int i = 0; i < m_Textures.size(); i++)
		{
			m_Textures[i]->Bind(i);
		}

		float textureID = (float)m_TextureID;

		float vertices[] = {
			120.0f, 120.0f, 0.0f, 0.0f, textureID,
			220.0f, 120.0f, 1.0f, 0.0f, textureID,
			220.0f, 220.0f, 1.0f, 1.0f, textureID,
			120.0f, 220.0f, 0.0f, 1.0f, textureID,
		};

		m_VBO->UpdateBufferSubData(0, 4 * sizeof(Vertex2D), vertices);

		renderer.Draw(*m_VAO, *m_EBO, *m_Shader);
	}

	void TestChangeTexture::OnImGuiRender()
	{
		ImGui::SliderInt("TextureID", &m_TextureID, 0, 2);
	}
}