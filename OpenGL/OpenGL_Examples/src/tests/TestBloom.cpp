#include "TestBloom.h"

namespace test {
	TestBloom::TestBloom()
		: m_EnableBloom(true)
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

		m_CubeVAO = std::make_unique<VertexArray>();
		m_CubeVBO = std::make_unique<VertexBuffer>(cubeVertices, 36 * 8 * sizeof(float), GL_STATIC_DRAW);

		VertexBufferLayout cubeLayout;
		cubeLayout.Push(GL_FLOAT, 3, GL_FALSE);
		cubeLayout.Push(GL_FLOAT, 3, GL_FALSE);
		cubeLayout.Push(GL_FLOAT, 2, GL_FALSE);
		m_CubeVAO->AddBuffer(*m_CubeVBO, cubeLayout);

		m_CubeTexture = std::make_unique<Texture>("res/textures/opengl/container2.png");
		m_CubeShader = std::make_unique<Shader>("res/shaders/lighting/bloom/Bloom.shader");
		m_CubeShader->Bind();
		m_CubeShader->SetUniform1i("u_Texture", 0);
		m_CubeShader->Unbind();

		m_LightShader = std::make_unique<Shader>("res/shaders/lighting/bloom/LightBox.shader");

		float quadVertices[] = {
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
			 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
			-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
		};

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
		m_HDRShader->SetUniform1i("u_HDR", true);
		m_HDRShader->SetUniform1f("u_Exposure", 0.8f);
		m_HDRShader->SetUniform1i("u_BloomBlur", 1);
		m_HDRShader->Unbind();

		m_BloomFBO = std::make_unique<FrameBuffer>(SCR_WIDTH, SCR_HEIGHT);
		m_BloomFBO->AttachTexture1f();
		m_BloomFBO->AttachTexture1f();

		m_RBO = std::make_unique<RenderBuffer>(SCR_WIDTH, SCR_HEIGHT);
		m_RBO->Configure();
		m_RBO->AttachBuffer();

		Renderer renderer;
		renderer.EnableColorBuffers(2);

		m_BloomFBO->Unbind();
		m_RBO->Unbind();

		m_BlurShader = std::make_unique<Shader>("res/shaders/lighting/bloom/GaussianBlur.shader");
		m_BlurShader->Bind();
		m_BlurShader->SetUniform1i("u_Image", 0);
		m_BlurShader->Unbind();

		// Two pass Gaussian blur framebuffers
		m_BlurFBO1 = std::make_unique<FrameBuffer>(SCR_WIDTH, SCR_HEIGHT);
		m_BlurFBO1->AttachTexture1f();
		m_BlurFBO1->Unbind();

		m_BlurFBO2 = std::make_unique<FrameBuffer>(SCR_WIDTH, SCR_HEIGHT);
		m_BlurFBO2->AttachTexture1f();
		m_BlurFBO2->Unbind();

		m_CubeVAO->Unbind();
		m_CubeVBO->Unbind();
		m_QuadVAO->Unbind();
		m_QuadVBO->Unbind();
		m_QuadEBO->Unbind();
	}

	TestBloom::~TestBloom()
	{
		glDisable(GL_DEPTH_TEST);
	}

	void TestBloom::OnUpdate(GLFWwindow* window, float deltaTime, Camera& camera)
	{
		camera.CameraInput(window, deltaTime);
		m_Transforms = camera.GetTransformMatrices();
	}

	void TestBloom::OnRender()
	{
		Renderer renderer;

		glEnable(GL_DEPTH_TEST);

		std::vector<glm::vec3> lightPositions = {
			glm::vec3(0.0f,  0.5f, 1.5f),
			glm::vec3(-4.0f, 0.5f, -3.0f),
			glm::vec3(3.0f, 0.5f, 1.0f),
			glm::vec3(-0.8f, 2.4f, -1.0f),
		};

		std::vector<glm::vec3> lightColors = {
			glm::vec3(5.0f, 5.0f, 5.0f),
			glm::vec3(10.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 15.0f),
			glm::vec3(0.0f, 5.0f, 0.0f)
		};

		m_BloomFBO->Bind();
		renderer.Clear();

		m_CubeTexture->Bind(0);

		m_CubeShader->Bind();
		m_CubeShader->SetUniformMat4f("u_Projection", m_Transforms.projection);
		m_CubeShader->SetUniformMat4f("u_View", m_Transforms.view);

		for (unsigned int i = 0; i < lightPositions.size(); i++)
		{
			m_CubeShader->SetUniform3f("u_Lights[" + std::to_string(i) + "].position", lightPositions[i].x, lightPositions[i].y, lightPositions[i].z);
			m_CubeShader->SetUniform3f("u_Lights[" + std::to_string(i) + "].color", lightColors[i].x, lightColors[i].y, lightColors[i].z);
		}

		glm::mat4 model = glm::mat4(1.0f);

		// Floor
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(12.5f, 0.5f, 12.5f));
		m_CubeShader->SetUniformMat4f("u_Model", model);
		renderer.Draw(*m_CubeVAO, *m_CubeShader, 36);

		// Scene cubes
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0));
		model = glm::scale(model, glm::vec3(0.5f));
		m_CubeShader->SetUniformMat4f("u_Model", model);
		renderer.Draw(*m_CubeVAO, *m_CubeShader, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 1.0));
		model = glm::scale(model, glm::vec3(0.5f));
		m_CubeShader->SetUniformMat4f("u_Model", model);
		renderer.Draw(*m_CubeVAO, *m_CubeShader, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.0f, -1.0f, 2.0));
		model = glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
		m_CubeShader->SetUniformMat4f("u_Model", model);
		renderer.Draw(*m_CubeVAO, *m_CubeShader, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 2.7f, 4.0));
		model = glm::rotate(model, glm::radians(23.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
		model = glm::scale(model, glm::vec3(1.25));
		m_CubeShader->SetUniformMat4f("u_Model", model);
		renderer.Draw(*m_CubeVAO, *m_CubeShader, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-2.0f, 1.0f, -3.0));
		model = glm::rotate(model, glm::radians(124.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
		m_CubeShader->SetUniformMat4f("u_Model", model);
		renderer.Draw(*m_CubeVAO, *m_CubeShader, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-3.0f, 0.0f, 0.0));
		model = glm::scale(model, glm::vec3(0.5f));
		m_CubeShader->SetUniformMat4f("u_Model", model);
		renderer.Draw(*m_CubeVAO, *m_CubeShader, 36);

		// Lights
		m_LightShader->Bind();
		m_LightShader->SetUniformMat4f("u_Projection", m_Transforms.projection);
		m_LightShader->SetUniformMat4f("u_View", m_Transforms.view);

		for (unsigned int i = 0; i < 4; i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, lightPositions[i]);
			model = glm::scale(model, glm::vec3(0.25f));
			m_LightShader->SetUniformMat4f("u_Model", model);
			m_LightShader->SetUniform3f("u_LightColor", lightColors[i].x, lightColors[i].y, lightColors[i].z);
			renderer.Draw(*m_CubeVAO, *m_LightShader, 36);
		}

		m_BloomFBO->Unbind();

		// Two pass Gaussian blur
		m_BlurShader->Bind();

		m_BlurFBO1->Bind();
		m_BloomFBO->BindTexture(0, 1);
		m_BlurShader->SetUniform1i("u_Horizontal", true); // Horizontal pass
		renderer.Draw(*m_QuadVAO, *m_QuadEBO, *m_BlurShader);

		m_BlurFBO2->Bind();
		m_BlurFBO1->BindTexture(0, 0);
		m_BlurShader->SetUniform1i("u_Horizontal", false); // Vertical pass
		renderer.Draw(*m_QuadVAO, *m_QuadEBO, *m_BlurShader);

		m_BlurFBO2->Unbind();
		renderer.Clear();

		m_BloomFBO->BindTexture(0, 0);
		m_BlurFBO2->BindTexture(1, 0);
		m_HDRShader->Bind();
		m_HDRShader->SetUniform1i("u_Bloom", m_EnableBloom);

		renderer.Draw(*m_QuadVAO, *m_QuadEBO, *m_HDRShader);
	}

	void TestBloom::OnImGuiRender()
	{
		ImGui::Checkbox("Bloom", &m_EnableBloom);
	}
}