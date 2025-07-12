#include "TestHDR.h"

namespace test {
	TestHDR::TestHDR()
		: m_EnableHDR(false), m_Exposure(1.0f)
	{
		float cubeVertices[] = {
			-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
			 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
			 1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
			 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
			-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
			-1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,

			-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
			 1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f,
			 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,
			 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,
			-1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,
			-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,

			-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
			-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
			-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
			-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,

			 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
			 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
			 1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
			 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
			 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
			 1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,

			 -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
			  1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
			  1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
			  1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
			 -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
			 -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,

			 -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
			  1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
			  1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
			  1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
			 -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
			 -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f
		};

		float quadVertices[] = {
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
			 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
			-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
		};

		m_CubeVAO = std::make_unique<VertexArray>();
		m_CubeVBO = std::make_unique<VertexBuffer>(cubeVertices, 36 * 8 * sizeof(float), GL_STATIC_DRAW);

		VertexBufferLayout cubeLayout;
		cubeLayout.Push(GL_FLOAT, 3, GL_FALSE);
		cubeLayout.Push(GL_FLOAT, 3, GL_FALSE);
		cubeLayout.Push(GL_FLOAT, 2, GL_FALSE);
		m_CubeVAO->AddBuffer(*m_CubeVBO, cubeLayout);

		m_Texture = std::make_unique<Texture>("res/textures/opengl/wood_floor.png");
		m_CubeShader = std::make_unique<Shader>("res/shaders/lighting/LightCast2.shader");
		m_CubeShader->Bind();
		m_CubeShader->SetUniform1i("u_Texture", 0);
		m_CubeShader->Unbind();

		unsigned int indices[] = {
			0, 1, 2, 2, 3, 0
		};

		m_QuadVAO = std::make_unique<VertexArray>();
		m_QuadEBO = std::make_unique<IndexBuffer>(indices, 6);
		m_QuadVBO = std::make_unique<VertexBuffer>(quadVertices, 4 * 5 * sizeof(float), GL_STATIC_DRAW);

		VertexBufferLayout quadLayout;
		quadLayout.Push(GL_FLOAT, 3, GL_FALSE);
		quadLayout.Push(GL_FLOAT, 2, GL_FALSE);
		m_QuadVAO->AddBuffer(*m_QuadVBO, quadLayout);

		m_HDRShader = std::make_unique<Shader>("res/shaders/lighting/HDR.shader");
		m_HDRShader->Bind();
		m_HDRShader->SetUniform1i("u_HDRBuffer", 0);
		m_HDRShader->Unbind();

		m_FBO = std::make_unique<FrameBuffer>(SCR_WIDTH, SCR_HEIGHT);
		m_FBO->AttachTexture1f();

		m_RBO = std::make_unique<RenderBuffer>(SCR_WIDTH, SCR_HEIGHT);
		m_RBO->Configure();

		m_FBO->Unbind();
		m_RBO->Unbind();

		m_CubeVAO->Unbind();
		m_CubeVBO->Unbind();
		m_QuadVAO->Unbind();
		m_QuadVBO->Unbind();
		m_QuadEBO->Unbind();
	}

	TestHDR::~TestHDR()
	{
		glDisable(GL_DEPTH_TEST);
	}

	void TestHDR::OnUpdate(GLFWwindow* window, float deltaTime, Camera& camera)
	{
		camera.CameraInput(window, deltaTime);
		m_Transforms = camera.GetTransformMatrices();
		m_ViewPos = camera.GetPosition();
	}

	void TestHDR::OnRender()
	{
		Renderer renderer;

		glEnable(GL_DEPTH_TEST);

		std::vector<glm::vec3> lightPositions = {
			glm::vec3(0.0f,  0.0f, 49.5f),
			glm::vec3(-1.4f, -1.9f, 9.0f),
			glm::vec3(0.0f, -1.8f, 4.0f),
			glm::vec3(0.8f, -1.7f, 6.0f),
		};

		std::vector<glm::vec3> lightColors = {
			glm::vec3(200.0f, 200.0f, 200.0f),
			glm::vec3(0.1f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.2f),
			glm::vec3(0.0f, 0.1f, 0.0f)
		};

		// Render scene into floating point framebuffer
		m_FBO->Bind();
		renderer.Clear();

		m_Texture->Bind(0);

		m_CubeShader->Bind();
		m_CubeShader->SetUniformMat4f("u_Projection", m_Transforms.projection);
		m_CubeShader->SetUniformMat4f("u_View", m_Transforms.view);

		for (unsigned int i = 0; i < lightPositions.size(); i++)
		{
			m_CubeShader->SetUniform3f("u_Lights[" + std::to_string(i) + "].position", lightPositions[i].x, lightPositions[i].y, lightPositions[i].z);
			m_CubeShader->SetUniform3f("u_Lights[" + std::to_string(i) + "].color", lightColors[i].x, lightColors[i].y, lightColors[i].z);
		}

		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 25.0f));
		model = glm::scale(model, glm::vec3(2.5f, 2.5f, 27.5f));

		m_CubeShader->SetUniformMat4f("u_Model", model);
		renderer.Draw(*m_CubeVAO, *m_CubeShader, 36);

		m_FBO->Unbind();
		renderer.Clear();

		m_HDRShader->Bind();
		m_FBO->BindTexture(0);
		m_HDRShader->SetUniform1f("u_HDR", m_EnableHDR);
		m_HDRShader->SetUniform1f("u_Exposure", m_Exposure);

		renderer.Draw(*m_QuadVAO, *m_QuadEBO, *m_HDRShader);
	}

	void TestHDR::OnImGuiRender()
	{
		if (ImGui::RadioButton("HDR disabled", !m_EnableHDR))
			m_EnableHDR = false;
		if (ImGui::RadioButton("HDR enabled", m_EnableHDR))
			m_EnableHDR = true;

		ImGui::SliderFloat("Exposure", &m_Exposure, 0.0f, 100.0f);
	}
}