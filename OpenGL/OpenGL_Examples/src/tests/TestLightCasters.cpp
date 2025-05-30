#include "TestLightCasters.h"

namespace test {
	TestLightCasters::TestLightCasters()
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
		}, m_LightType(LightType::DIRECTIONAL)
	{
		float vertices[] = {
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
		};

		m_ContainerVAO = std::make_unique<VertexArray>();
		m_VBO = std::make_unique<VertexBuffer>(vertices, 36 * 8 * sizeof(float), GL_STATIC_DRAW);

		VertexBufferLayout layout;
		layout.Push(GL_FLOAT, 3, GL_FALSE);
		layout.Push(GL_FLOAT, 3, GL_FALSE);
		layout.Push(GL_FLOAT, 2, GL_FALSE);
		m_ContainerVAO->AddBuffer(*m_VBO, layout);

		m_LightVAO = std::make_unique<VertexArray>();
		m_LightVAO->AddBuffer(*m_VBO, layout);

		m_ContainerDiffuse = std::make_unique<Texture>("res/textures/opengl/container2.png");
		m_ContainerSpecular = std::make_unique<Texture>("res/textures/opengl/container2_specular.png");
		m_ContainerShader = std::make_unique<Shader>("res/shaders/LightCast.shader");

		m_ContainerShader->Bind();
		m_ContainerShader->SetUniform1i("u_Material.diffuse", 0);
		m_ContainerShader->SetUniform1i("u_Material.specular", 1);

		m_LightTexture = std::make_unique<Texture>("res/textures/minecraft/glowstone.jpg");
		m_LightShader = std::make_unique<Shader>("res/shaders/LightCube.shader");

		m_LightShader->Bind();
		m_LightShader->SetUniform1i("u_Texture", 0);
	}

	TestLightCasters::~TestLightCasters()
	{
		glDisable(GL_DEPTH_TEST);
	}

	void TestLightCasters::OnRender()
	{
		Renderer renderer;

		glEnable(GL_DEPTH_TEST);

		m_ContainerDiffuse->Bind(0);
		m_ContainerSpecular->Bind(1);

		m_ContainerShader->Bind();

		glm::mat4 projection = glm::perspective(m_FoV, 960.0f / 540.0f, 0.1f, 100.0f);

		m_ContainerShader->SetUniformMat4f("u_View", m_View);
		m_ContainerShader->SetUniformMat4f("u_Projection", projection);

		m_ContainerShader->SetUniform3f("u_ViewPosition", m_ViewPos.x, m_ViewPos.y, m_ViewPos.z);

		m_ContainerShader->SetUniform1f("u_Material.shininess", 32.0f);

		if (m_LightType == LightType::DIRECTIONAL)
		{
			m_ContainerShader->SetUniform4f("u_Light.direction", -0.2f, -1.0f, -0.3f, 0.0f);
		}
		else if (m_LightType == LightType::POINT)
		{
			m_ContainerShader->SetUniform4f("u_Light.direction", 0.0f, 0.0f, 0.0f, 1.0f);
			m_ContainerShader->SetUniform3f("u_Light.position", 1.2f, 1.0f, 2.0f);
		}
		else if (m_LightType == LightType::SPOT)
		{
			m_ContainerShader->SetUniform4f("u_Light.direction", m_ViewFront.x, m_ViewFront.y, m_ViewFront.z, 2.0);
			m_ContainerShader->SetUniform3f("u_Light.position", m_ViewPos.x, m_ViewPos.y, m_ViewPos.z);
			// Calculating the cosine value of the cutof angle saves performance in the shader
			m_ContainerShader->SetUniform1f("u_Light.innerCutOff", glm::cos(glm::radians(12.5f)));
			m_ContainerShader->SetUniform1f("u_Light.outerCutOff", glm::cos(glm::radians(17.5)));
		}

		m_ContainerShader->SetUniform3f("u_Light.ambient", 0.2f, 0.2f, 0.2f);
		m_ContainerShader->SetUniform3f("u_Light.diffuse", 0.5f, 0.5f, 0.5f);
		m_ContainerShader->SetUniform3f("u_Light.specular", 1.0f, 1.0f, 1.0f);

		m_ContainerShader->SetUniform1f("u_Light.constant", 1.0f);
		m_ContainerShader->SetUniform1f("u_Light.linear", 0.09f);
		m_ContainerShader->SetUniform1f("u_Light.quadratic", 0.032f);

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

			m_ContainerShader->SetUniformMat4f("u_Model", model);

			renderer.Draw(*m_ContainerVAO, *m_ContainerShader, 36);
		}

		m_LightTexture->Bind(0);
		m_LightShader->Bind();

		glm::vec3 lightPosition(2.0f, 1.5f, 2.0f);
		glm::mat4 model = glm::translate(glm::mat4(1.0f), lightPosition);
		model = glm::scale(model, glm::vec3(0.2f));

		m_LightShader->SetUniformMat4f("u_MVP", projection * m_View * model);

		renderer.Draw(*m_LightVAO, *m_LightShader, 36);
	}

	void TestLightCasters::OnUpdate(GLFWwindow* window, float deltaTime, Camera* camera)
	{
		camera->CameraInput(window, deltaTime);
		m_View = camera->GetLookAt();
		m_FoV = camera->GetZoom();
		m_ViewPos = camera->GetPosition();
		m_ViewFront = camera->GetFront();
	}

	void TestLightCasters::OnImGuiRender()
	{
		ImGui::SliderInt("Light Type", &m_LightType, 0, 3);
	}
}