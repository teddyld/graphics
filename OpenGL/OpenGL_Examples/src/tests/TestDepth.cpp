#include "TestDepth.h"

namespace test {
	TestDepth::TestDepth()
		: m_DepthFunc(2)
	{
		float cubeVertices[] = {
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

			-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
			 0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
			 0.5f, 0.5f,  0.5f, 1.0f, 0.0f,
			 0.5f, 0.5f,  0.5f, 1.0f, 0.0f,
			-0.5f, 0.5f,  0.5f, 0.0f, 0.0f,
			-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
		};

		float planeVertices[] = {
			 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
			-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
			-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

			 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
			-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
			 5.0f, -0.5f, -5.0f,  2.0f, 2.0f
		};

		m_CubeVAO = std::make_unique<VertexArray>();
		m_CubeVBO = std::make_unique<VertexBuffer>(cubeVertices, 36 * 5 * sizeof(float), GL_STATIC_DRAW);

		VertexBufferLayout layout;
		layout.Push(GL_FLOAT, 3, GL_FALSE);
		layout.Push(GL_FLOAT, 2, GL_FALSE);
		m_CubeVAO->AddBuffer(*m_CubeVBO, layout);

		m_PlaneVAO = std::make_unique<VertexArray>();
		m_PlaneVBO = std::make_unique<VertexBuffer>(planeVertices, 6 * 5 * sizeof(float), GL_STATIC_DRAW);
		m_PlaneVAO->AddBuffer(*m_PlaneVBO, layout);

		m_Shader = std::make_unique<Shader>("res/shaders/Depth.shader");

		m_CubeVAO->Unbind();
		m_CubeVBO->Unbind();
		m_PlaneVAO->Unbind();
		m_PlaneVBO->Unbind();
	}

	TestDepth::~TestDepth()
	{
		glDisable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS); // Default value
	}

	void TestDepth::OnUpdate(GLFWwindow* window, float deltaTime, Camera& camera)
	{
		camera.CameraInput(window, deltaTime);
		m_Transforms = camera.GetTransformMatrices();
	}

	void TestDepth::OnRender()
	{
		Renderer renderer;

		glEnable(GL_DEPTH_TEST);

		glm::mat4 projection = m_Transforms.projection;
		glm::mat4 view = m_Transforms.view;

		m_Shader->Bind();

		// First cube
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, -1.0f));
		m_Shader->SetUniformMat4f("u_MVP", projection * view * model);
		renderer.Draw(*m_CubeVAO, *m_Shader, 36);

		// Second cube
		model = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f));
		m_Shader->SetUniformMat4f("u_MVP", projection * view * model);
		renderer.Draw(*m_CubeVAO, *m_Shader, 36);

		// Plane
		m_Shader->SetUniformMat4f("u_MVP", projection * view);
		renderer.Draw(*m_PlaneVAO, *m_Shader, 6);
	}

	void TestDepth::OnImGuiRender()
	{
		std::vector<std::pair<const char*, GLenum>> m_Options = {
			{ "GL_ALWAYS", GL_ALWAYS },
			{ "GL_NEVER", GL_NEVER },
			{ "GL_LESS", GL_LESS },
			{ "GL_EQUAL", GL_EQUAL },
			{ "GL_LEQUAL", GL_LEQUAL },
			{ "GL_GREATER", GL_GREATER },
			{ "GL_NOTEQUAL", GL_NOTEQUAL },
			{ "GL_GEQUAL", GL_GEQUAL }
		};

		if (ImGui::BeginCombo("Depth test function", m_Options[m_DepthFunc].first))
		{
			for (int n = 0; n < m_Options.size(); n++)
			{
				bool is_selected = m_DepthFunc == n;
				if (ImGui::Selectable(m_Options[n].first, is_selected))
				{
					m_DepthFunc = n;
					glDepthFunc(m_Options[m_DepthFunc].second);
				}
			}
			ImGui::EndCombo();
		}
	}
}