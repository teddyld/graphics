#include "TestTransform3D.h"

namespace test {
	TestTransform3D::TestTransform3D()
		: m_CubePositions{
			glm::vec3(0.0f,  0.0f,  0.0f),
			glm::vec3(2.0f,  5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3(2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3(1.3f, -2.0f, -2.5f),
			glm::vec3(1.5f,  2.0f, -2.5f),
			glm::vec3(1.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
		}
	{
		glEnable(GL_DEPTH_TEST);

		float vertices[] = {
			 -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
			 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
			-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,

			 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
			 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
			 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,

			-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
			-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,

			-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		};

		m_VAO = std::make_unique<VertexArray>();
		m_VBO = std::make_unique<VertexBuffer>(vertices, 36 * 10 * sizeof(float), GL_STATIC_DRAW);

		VertexBufferLayout layout;
		layout.Push(GL_FLOAT, 3, GL_FALSE);
		layout.Push(GL_FLOAT, 2, GL_FALSE);
		layout.Push(GL_FLOAT, 1, GL_FALSE);
		m_VAO->AddBuffer(*m_VBO, layout);

		m_TextureGrassBottom = std::make_unique<Texture>("res/textures/minecraft/grass_bottom.jpg");

		m_Shader = std::make_unique<Shader>("res/shaders/Texture16.shader");
		m_Shader->Bind();

		int samplers[1] = { 0 };
		m_Shader->SetUniform1iv("u_Textures", 1, samplers);

		m_VAO->Unbind();
		m_VBO->Unbind();
		m_Shader->Unbind();
	}

	TestTransform3D::~TestTransform3D()
	{
		glDisable(GL_DEPTH_TEST);
	}

	void TestTransform3D::OnUpdate(GLFWwindow* window, float deltaTime, Camera* camera)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		camera->CameraKeyboardInput(window, deltaTime);
		m_View = camera->GetLookAt();
		m_FoV = camera->GetZoom();
	}

	void TestTransform3D::OnRender()
	{
		Renderer renderer;

		m_TextureGrassBottom->Bind(0);

		glm::mat4 view = m_View;
		glm::mat4 projection = glm::perspective(m_FoV, 960.0f / 540.0f, 0.1f, 100.0f);

		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, m_CubePositions[i]);

			if (i % 3 == 0)
			{
				model = glm::rotate(model, (float)glfwGetTime() * glm::radians(20.0f), glm::vec3(1.0f, 0.3f, 0.5f));
			}
			else
			{
				float angle = 20.0f * i;
				model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			}

			glm::mat4 mvp = projection * view * model;
			m_Shader->SetUniformMat4f("u_MVP", mvp);

			renderer.Draw(*m_VAO, *m_Shader, 36);
		}
	}
}