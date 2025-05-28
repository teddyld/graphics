#include "TestLighting.h"

namespace test {
	TestLighting::TestLighting()
		: m_AmbientStrength(0.1f), m_SpecularStrength(0.5f), m_Shininess(32), m_LightColor{ 1.0, 1.0, 1.0 }, m_ShaderType(0)
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

		m_ObjectVAO = std::make_unique<VertexArray>();

		m_VBO = std::make_unique<VertexBuffer>(vertices, 36 * 8 * sizeof(float), GL_STATIC_DRAW);

		VertexBufferLayout layout;
		layout.Push(GL_FLOAT, 3, GL_FALSE);
		layout.Push(GL_FLOAT, 3, GL_FALSE);
		layout.Push(GL_FLOAT, 2, GL_FALSE);
		m_ObjectVAO->AddBuffer(*m_VBO, layout);

		m_LightVAO = std::make_unique<VertexArray>();
		m_LightVAO->AddBuffer(*m_VBO, layout);

		m_LightShader = std::make_unique<Shader>("res/shaders/Light.shader");

		m_Container = std::make_unique<Texture>("res/textures/opengl/container.jpg");
		m_Glowstone = std::make_unique<Texture>("res/textures/minecraft/glowstone.jpg");

		m_LightShader->Bind();
		m_LightShader->SetUniform1i("u_Texture", 0);
	}

	TestLighting::~TestLighting()
	{
		glDisable(GL_DEPTH_TEST);
	}

	void TestLighting::OnRender()
	{
		Renderer renderer;

		glEnable(GL_DEPTH_TEST);

		glm::vec3 lightPosition(2.0 * sin(glfwGetTime()), 1.5f, 2.0 * cos(glfwGetTime()));
		glm::mat4 projection = glm::perspective(m_FoV, 960.0f / 540.0f, 0.1f, 100.0f);
		glm::mat4 objectModel = glm::mat4(1.0f);

		// Render the cube object
		m_Container->Bind(0);

		if (m_ShaderType == 0)
			m_ObjectShader = std::make_unique<Shader>("res/shaders/PhongObject.shader");
		else
			m_ObjectShader = std::make_unique<Shader>("res/shaders/GouradObject.shader");

		m_ObjectShader->Bind();

		m_ObjectShader->SetUniform1i("u_Texture", 0);

		m_ObjectShader->SetUniformMat4f("u_Model", objectModel);
		m_ObjectShader->SetUniformMat4f("u_View", m_View);
		m_ObjectShader->SetUniformMat4f("u_Projection", projection);

		m_ObjectShader->SetUniform3f("u_LightColor", m_LightColor[0], m_LightColor[1], m_LightColor[2]);
		m_ObjectShader->SetUniform3f("u_LightPosition", lightPosition.x, lightPosition.y, lightPosition.z);
		m_ObjectShader->SetUniform3f("u_ViewPosition", m_ViewPos.x, m_ViewPos.y, m_ViewPos.z);

		m_ObjectShader->SetUniform1f("u_AmbientStrength", m_AmbientStrength);
		m_ObjectShader->SetUniform1f("u_SpecularStrength", m_SpecularStrength);
		m_ObjectShader->SetUniform1i("u_Shininess", m_Shininess);

		renderer.Draw(*m_ObjectVAO, *m_ObjectShader, 36);

		// Render the light object
		m_Glowstone->Bind(0);
		m_LightShader->Bind();

		glm::mat4 model = glm::translate(glm::mat4(1.0f), lightPosition);
		model = glm::scale(model, glm::vec3(0.2f));

		m_LightShader->SetUniformMat4f("u_MVP", projection * m_View * model);

		renderer.Draw(*m_LightVAO, *m_LightShader, 36);
	}

	void TestLighting::OnUpdate(GLFWwindow* window, float deltaTime, Camera* camera)
	{
		camera->CameraInput(window, deltaTime);
		m_View = camera->GetLookAt();
		m_FoV = camera->GetZoom();
		m_ViewPos = camera->GetPosition();
	}

	void TestLighting::OnImGuiRender()
	{
		ImGui::ColorEdit3("Light Color", m_LightColor);
		ImGui::SliderInt("Phong shading <-> Gourad shading", &m_ShaderType, 0, 1);
		ImGui::Spacing();
		ImGui::SliderFloat("Ambient Strength", &m_AmbientStrength, 0.0, 1.0);
		ImGui::SliderFloat("Specular Strength", &m_SpecularStrength, 0.0, 1.0);
		ImGui::SliderInt("Shininess Factor", &m_Shininess, 0, 128);
	}
}