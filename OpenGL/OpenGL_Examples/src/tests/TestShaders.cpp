#include "TestShaders.h"

namespace test {
	TestShaders::TestShaders()
	{
		float vertices[] = {
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,
		};

		unsigned int indices[] = {
			0, 1, 2, 2, 3, 0
		};

		m_VAO = std::make_unique<VertexArray>();
		m_EBO = std::make_unique<IndexBuffer>(indices, 6);
		m_VBO = std::make_unique<VertexBuffer>(vertices, 4 * 2 * sizeof(float), GL_STATIC_DRAW);

		VertexBufferLayout layout;
		layout.Push(GL_FLOAT, 2, GL_FALSE);
		m_VAO->AddBuffer(*m_VBO, layout);

		m_Shader = std::make_unique<Shader>("res/shaders/Fractal.shader");
	}

	void TestShaders::OnUpdate(GLFWwindow* window, float deltaTime, Camera& camera)
	{
		m_Shader->Bind();

		int width, height;
		glfwGetFramebufferSize(window, &width, &height);

		m_Shader->SetUniform1f("u_Time", (float)glfwGetTime());
		m_Shader->SetUniform2i("u_Resolution", width, height);
	}

	void TestShaders::OnRender()
	{
		Renderer renderer;

		glm::mat4 projection = glm::ortho(0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 1.0f);

		m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_MVP", projection);

		renderer.Draw(*m_VAO, *m_EBO, *m_Shader);
	}

	void TestShaders::OnImGuiRender()
	{
	}
}