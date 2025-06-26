#include "TestGammaCorrection.h"

namespace test {
	TestGammaCorrection::TestGammaCorrection()
		: m_GammaCorrection(false), m_Gamma(2.2f), m_Attenuation(false)
	{
		float planeVertices[] = {
			 10.0, -0.5f,  10.0, 0.0f, 1.0f, 0.0f, 10.0f, 0.0f,
			-10.0, -0.5f,  10.0, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
			-10.0, -0.5f, -10.0, 0.0f, 1.0f, 0.0f, 0.0f, 10.0f,

			 10.0, -0.5f,  10.0, 0.0f, 1.0f, 0.0f, 10.0f, 0.0f,
			-10.0, -0.5f, -10.0, 0.0f, 1.0f, 0.0f, 0.0f, 10.0f,
			 10.0, -0.5f, -10.0, 0.0f, 1.0f, 0.0f, 10.0f, 10.0f
		};

		m_VAO = std::make_unique<VertexArray>();
		m_VBO = std::make_unique<VertexBuffer>(planeVertices, 6 * 8 * sizeof(float), GL_STATIC_DRAW);

		VertexBufferLayout layout;
		layout.Push(GL_FLOAT, 3, GL_FALSE);
		layout.Push(GL_FLOAT, 3, GL_FALSE);
		layout.Push(GL_FLOAT, 2, GL_FALSE);
		m_VAO->AddBuffer(*m_VBO, layout);

		m_Shader = std::make_unique<Shader>("res/shaders/lighting/GammaCorrection.shader");

		std::map<GLenum, GLint> options = {
			{ GL_TEXTURE_MIN_FILTER, GL_LINEAR },
			{ GL_TEXTURE_MAG_FILTER, GL_LINEAR },
			{ GL_TEXTURE_WRAP_S, GL_REPEAT },
			{ GL_TEXTURE_WRAP_T, GL_REPEAT },
		};

		// Set internal format to GL_SRGB_ALPHA to avoid gamma correcting the texture twice
		m_GammaCorrectedTexture = std::make_unique<Texture>("res/textures/opengl/wood_floor.png", GL_TEXTURE_2D, options, true);
		m_Texture = std::make_unique<Texture>("res/textures/opengl/wood_floor.png", GL_TEXTURE_2D, options, false);

		m_VAO->Unbind();
		m_VBO->Unbind();
	}

	TestGammaCorrection::~TestGammaCorrection()
	{
		glDisable(GL_DEPTH_TEST);
	}

	void TestGammaCorrection::OnUpdate(GLFWwindow* window, float deltaTime, Camera& camera)
	{
		camera.CameraInput(window, deltaTime);
		m_Transforms = camera.GetTransformMatrices();
		m_ViewPos = camera.GetPosition();
	}

	void TestGammaCorrection::OnRender()
	{
		Renderer renderer;

		glEnable(GL_DEPTH_TEST);

		std::vector<glm::vec3> lightPositions = {
			glm::vec3(-3.0f, 0.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(3.0f, 0.0f, 0.0f)
		};

		std::vector<glm::vec3> lightColors = {
			glm::vec3(0.25f), glm::vec3(0.50f), glm::vec3(0.75f), glm::vec3(1.0f)
		};

		if (m_GammaCorrection)
			m_GammaCorrectedTexture->Bind(0);
		else
			m_Texture->Bind(0);

		m_Shader->Bind();
		m_Shader->SetUniform1i("u_GammaCorrection", m_GammaCorrection);
		m_Shader->SetUniform1f("u_Gamma", m_Gamma);
		m_Shader->SetUniform1i("u_Attenuation", m_Attenuation);

		m_Shader->SetUniform1i("U_Material.diffuse", 0);
		m_Shader->SetUniform1f("u_Material.shininess", 32.0f);

		m_Shader->SetUniformMat4f("u_Model", glm::mat4(1.0f));
		m_Shader->SetUniformMat4f("u_View", m_Transforms.view);
		m_Shader->SetUniformMat4f("u_Projection", m_Transforms.projection);
		m_Shader->SetUniform3f("u_ViewPosition", m_ViewPos.x, m_ViewPos.y, m_ViewPos.z);

		for (int i = 0; i < 4; i++)
		{
			m_Shader->SetUniform3f("u_Lights[" + std::to_string(i) + "].position", lightPositions[i].x, lightPositions[i].y, lightPositions[i].z);
			m_Shader->SetUniform3f("u_Lights[" + std::to_string(i) + "].diffuse", lightColors[i].x, lightColors[i].y, lightColors[i].z);
			m_Shader->SetUniform3f("u_Lights[" + std::to_string(i) + "].ambient", 0.05f, 0.05f, 0.05f);
			m_Shader->SetUniform3f("u_Lights[" + std::to_string(i) + "].specular", 0.3f, 0.3f, 0.3f);
		}

		renderer.Draw(*m_VAO, *m_Shader, 6);
	}

	void TestGammaCorrection::OnImGuiRender()
	{
		if (ImGui::RadioButton("No gamma correction", !m_GammaCorrection))
			m_GammaCorrection = false;
		if (ImGui::RadioButton("Gamma correction", m_GammaCorrection))
			m_GammaCorrection = true;
		ImGui::SliderFloat("Gamma value", &m_Gamma, 0.0, 100.0);

		if (ImGui::RadioButton("No attenuation", !m_Attenuation))
			m_Attenuation = false;
		if (ImGui::RadioButton("Attenuation", m_Attenuation))
			m_Attenuation = true;
	}
}