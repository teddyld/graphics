#include "TestCubemaps.h"

namespace test {
	TestCubemaps::TestCubemaps()
		: m_EnvironmentMapping(EnvironmentMapping::REFLECTIVE), m_From(0), m_To(3), m_RefractiveIndex(0.658f)
	{
		float skyboxVertices[] = {
			-1.0f,  1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			-1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f
		};

		float cubeVertices[] = {
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
		};

		m_SkyboxVAO = std::make_unique<VertexArray>();
		m_SkyboxVBO = std::make_unique<VertexBuffer>(skyboxVertices, 3 * 36 * sizeof(float), GL_STATIC_DRAW);
		VertexBufferLayout skyboxLayout;
		skyboxLayout.Push(GL_FLOAT, 3, GL_FALSE);
		m_SkyboxVAO->AddBuffer(*m_SkyboxVBO, skyboxLayout);

		m_SkyboxTexture = std::make_unique<Texture>("res/textures/opengl/skybox", GL_TEXTURE_CUBE_MAP);
		m_SkyboxShader = std::make_unique<Shader>("res/shaders/Skybox.shader");
		m_SkyboxShader->Bind();
		m_SkyboxShader->SetUniform1i("u_Skybox", 0);

		m_SkyboxShader->Unbind();

		m_ObjectVAO = std::make_unique<VertexArray>();
		m_ObjectVBO = std::make_unique<VertexBuffer>(cubeVertices, 6 * 36 * sizeof(float), GL_STATIC_DRAW);
		VertexBufferLayout objectLayout;
		objectLayout.Push(GL_FLOAT, 3, GL_FALSE);
		objectLayout.Push(GL_FLOAT, 3, GL_FALSE);
		m_ObjectVAO->AddBuffer(*m_ObjectVBO, objectLayout);

		m_ReflectiveShader = std::make_unique<Shader>("res/shaders/CubemapReflective.shader");
		m_ReflectiveShader->Bind();
		m_ReflectiveShader->SetUniform1i("u_Skybox", 0);
		m_ReflectiveShader->Unbind();

		m_RefractiveShader = std::make_unique<Shader>("res/shaders/CubemapRefractive.shader");
		m_RefractiveShader->Bind();
		m_RefractiveShader->SetUniform1i("u_Skybox", 0);
		m_RefractiveShader->Unbind();
	}

	TestCubemaps::~TestCubemaps()
	{
		glDisable(GL_DEPTH_TEST);
	}

	void TestCubemaps::OnUpdate(GLFWwindow* window, float deltaTime, Camera& camera)
	{
		camera.CameraInput(window, deltaTime);
		m_View = camera.GetLookAt();
		m_FoV = camera.GetZoom();
		m_CameraPos = camera.GetPosition();
	}

	void TestCubemaps::OnRender()
	{
		Renderer renderer;

		glEnable(GL_DEPTH_TEST);
		glm::mat4 projection = glm::perspective(glm::radians(m_FoV), 960.0f / 540.0f, 0.1f, 100.0f);
		m_SkyboxTexture->Bind(0);

		if (m_EnvironmentMapping == EnvironmentMapping::REFLECTIVE)
		{
			m_ReflectiveShader->Bind();

			m_ReflectiveShader->SetUniformMat4f("u_Model", glm::mat4(1.0f));
			m_ReflectiveShader->SetUniformMat4f("u_View", m_View);
			m_ReflectiveShader->SetUniformMat4f("u_Projection", projection);
			m_ReflectiveShader->SetUniform3f("u_CameraPos", m_CameraPos.x, m_CameraPos.y, m_CameraPos.z);

			renderer.Draw(*m_ObjectVAO, *m_ReflectiveShader, 36);
		}
		else if (m_EnvironmentMapping == EnvironmentMapping::REFRACTION)
		{
			m_RefractiveShader->Bind();
			m_RefractiveShader->SetUniform1f("u_RefractiveIndex", m_RefractiveIndex);

			m_RefractiveShader->SetUniformMat4f("u_Model", glm::mat4(1.0f));
			m_RefractiveShader->SetUniformMat4f("u_View", m_View);
			m_RefractiveShader->SetUniformMat4f("u_Projection", projection);
			m_RefractiveShader->SetUniform3f("u_CameraPos", m_CameraPos.x, m_CameraPos.y, m_CameraPos.z);

			renderer.Draw(*m_ObjectVAO, *m_RefractiveShader, 36);
		}

		glDepthFunc(GL_LEQUAL); // Change depth test so that it passes when values are also equal to depth buffer content
		m_SkyboxShader->Bind();
		m_SkyboxTexture->Bind(0);

		glm::mat4 view = glm::mat4(glm::mat3(m_View)); // Remove the translation component of the view matrix so that the skybox does not move with the camera
		glm::mat4 skyboxMVP = projection * view;
		m_SkyboxShader->SetUniformMat4f("u_MVP", skyboxMVP);

		renderer.Draw(*m_SkyboxVAO, *m_SkyboxShader, 36);

		glDepthFunc(GL_LESS); // Reset depth function
	}

	void TestCubemaps::OnImGuiRender()
	{
		std::vector<const char*> options = { "Reflection", "Refraction" };

		if (ImGui::BeginCombo("Environment mapping technique", options[m_EnvironmentMapping]))
		{
			for (int n = 0; n < options.size(); n++)
			{
				bool is_selected = m_EnvironmentMapping == n;
				if (ImGui::Selectable(options[n], is_selected))
				{
					m_EnvironmentMapping = options[n] == "Reflection" ? EnvironmentMapping::REFLECTIVE : EnvironmentMapping::REFRACTION;
				}

				if (is_selected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}

		ImGui::Spacing();
		ImGui::Text("Refractive index");

		std::vector<const char*> materials = { "Air", "Water", "Ice", "Glass", "Diamond" };
		std::map<const char*, float> refractiveMaterials = {
			{ "Air", 1.00f },
			{ "Water", 1.33f },
			{ "Ice", 1.309f },
			{ "Glass", 1.52f },
			{ "Diamond", 2.42f }
		};

		if (ImGui::BeginCombo("From", materials[m_From]))
		{
			for (int n = 0; n < materials.size(); n++)
			{
				bool is_selected = m_From == n;
				if (ImGui::Selectable(materials[n], is_selected))
				{
					m_From = n;
					m_RefractiveIndex = refractiveMaterials[materials[m_From]] / refractiveMaterials[materials[m_To]];
				}

				if (is_selected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}

		if (ImGui::BeginCombo("To", materials[m_To]))
		{
			for (int n = 0; n < materials.size(); n++)
			{
				bool is_selected = m_To == n;
				if (ImGui::Selectable(materials[n], is_selected))
				{
					m_To = n;
					m_RefractiveIndex = refractiveMaterials[materials[m_From]] / refractiveMaterials[materials[m_To]];
				}

				if (is_selected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}
	}
}