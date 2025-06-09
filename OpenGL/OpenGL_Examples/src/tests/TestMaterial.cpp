#include "TestMaterial.h"

namespace test {
	TestMaterial::TestMaterial()
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

		m_ContainerShader = std::make_unique<Shader>("res/shaders/Material.shader");
		m_LightShader = std::make_unique<Shader>("res/shaders/LightCube.shader");

		m_ContainerDiffuse = std::make_unique<Texture>("res/textures/opengl/container2.png");
		m_ContainerSpecular = std::make_unique<Texture>("res/textures/opengl/container2_specular.png");
		m_ContainerEmission = std::make_unique<Texture>("res/textures/opengl/matrix.jpg");

		m_LightTexture = std::make_unique<Texture>("res/textures/minecraft/glowstone.jpg");

		m_ContainerShader->Bind();
		m_ContainerShader->SetUniform1i("u_Material.diffuse", 0);
		m_ContainerShader->SetUniform1i("u_Material.specular", 1);
		m_ContainerShader->SetUniform1i("u_Material.emission", 2);

		m_LightShader->Bind();
		m_LightShader->SetUniform1i("u_Texture", 0);
	}

	TestMaterial::~TestMaterial()
	{
		glDisable(GL_DEPTH_TEST);
	}

	void TestMaterial::OnRender()
	{
		Renderer renderer;

		glEnable(GL_DEPTH_TEST);

		glm::vec3 lightPosition(2.0 * sin(glfwGetTime()), 1.5f, 2.0 * cos(glfwGetTime()));
		glm::mat4 projection = glm::perspective(glm::radians(m_FoV), 960.0f / 540.0f, 0.1f, 100.0f);
		glm::mat4 objectModel = glm::mat4(1.0f);

		// Render the cube object
		m_ContainerDiffuse->Bind(0);
		m_ContainerSpecular->Bind(1);
		m_ContainerEmission->Bind(2);

		m_ContainerShader->Bind();

		m_ContainerShader->SetUniformMat4f("u_Model", objectModel);
		m_ContainerShader->SetUniformMat4f("u_View", m_View);
		m_ContainerShader->SetUniformMat4f("u_Projection", projection);

		m_ContainerShader->SetUniform3f("u_ViewPosition", m_ViewPos.x, m_ViewPos.y, m_ViewPos.z);
		m_ContainerShader->SetUniform1f("u_Time", (float)glfwGetTime());

		m_ContainerShader->SetUniform1f("u_Material.shininess", 32.0f);

		m_ContainerShader->SetUniform3f("u_Light.position", lightPosition.x, lightPosition.y, lightPosition.z);
		m_ContainerShader->SetUniform3f("u_Light.ambient", 0.2f, 0.2f, 0.2f);
		m_ContainerShader->SetUniform3f("u_Light.diffuse", 0.5f, 0.5f, 0.5f);
		m_ContainerShader->SetUniform3f("u_Light.specular", 1.0f, 1.0f, 1.0f);

		renderer.Draw(*m_ContainerVAO, *m_ContainerShader, 36);

		// Render the light object
		m_LightTexture->Bind(0);
		m_LightShader->Bind();

		glm::mat4 model = glm::translate(glm::mat4(1.0f), lightPosition);
		model = glm::scale(model, glm::vec3(0.2f));

		m_LightShader->SetUniformMat4f("u_MVP", projection * m_View * model);

		renderer.Draw(*m_LightVAO, *m_LightShader, 36);
	}

	void TestMaterial::OnUpdate(GLFWwindow* window, float deltaTime, Camera& camera)
	{
		camera.CameraInput(window, deltaTime);
		m_View = camera.GetLookAt();
		m_FoV = camera.GetZoom();
		m_ViewPos = camera.GetPosition();
	}

	void TestMaterial::OnImGuiRender()
	{
	}
}