#include "TestBlinnPhong.h"

namespace test {
	TestBlinnPhong::TestBlinnPhong()
		: m_Blinn(false), m_AmbientStrength(0.05f), m_SpecularStrength(0.3f), m_Shininess(0.5f)
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

		std::map<GLenum, GLint> options = {
			{ GL_TEXTURE_MIN_FILTER, GL_LINEAR },
			{ GL_TEXTURE_MAG_FILTER, GL_LINEAR },
			{ GL_TEXTURE_WRAP_S, GL_REPEAT },
			{ GL_TEXTURE_WRAP_T, GL_REPEAT },
		};

		m_Texture = std::make_unique<Texture>("res/textures/opengl/wood_floor.png", GL_TEXTURE_2D, options);

		m_VAO->Unbind();
		m_VBO->Unbind();
	}

	TestBlinnPhong::~TestBlinnPhong()
	{
		glDisable(GL_DEPTH_TEST);
	}

	void TestBlinnPhong::OnUpdate(GLFWwindow* window, float deltaTime, Camera& camera)
	{
		camera.CameraInput(window, deltaTime);
		m_Transforms = camera.GetTransformMatrices();
		m_ViewPos = camera.GetPosition();
	}

	void TestBlinnPhong::OnRender()
	{
		Renderer renderer;

		glEnable(GL_DEPTH_TEST);

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = m_Transforms.view;
		glm::mat4 projection = m_Transforms.projection;

		glm::vec3 lightPosition = glm::vec3(0.0f, 0.0f, 0.0f);

		m_Texture->Bind(0);

		if (m_Blinn)
			m_PlaneShader = std::make_unique<Shader>("res/shaders/lighting/BlinnPhongObject.shader");

		else
			m_PlaneShader = std::make_unique<Shader>("res/shaders/lighting/PhongObject.shader");

		m_PlaneShader->Bind();
		m_PlaneShader->SetUniform1i("u_Material.diffuse", 0);
		m_PlaneShader->SetUniform1f("u_Material.shininess", m_Shininess);

		m_PlaneShader->SetUniformMat4f("u_Model", model);
		m_PlaneShader->SetUniformMat4f("u_View", view);
		m_PlaneShader->SetUniformMat4f("u_Projection", projection);
		m_PlaneShader->SetUniform3f("u_ViewPosition", m_ViewPos.x, m_ViewPos.y, m_ViewPos.z);

		m_PlaneShader->SetUniform3f("u_Light.position", lightPosition.x, lightPosition.y, lightPosition.z);
		m_PlaneShader->SetUniform3f("u_Light.diffuse", 1.0f, 1.0f, 1.0f);
		m_PlaneShader->SetUniform3f("u_Light.ambient", m_AmbientStrength, m_AmbientStrength, m_AmbientStrength);
		m_PlaneShader->SetUniform3f("u_Light.specular", m_SpecularStrength, m_SpecularStrength, m_SpecularStrength);

		renderer.Draw(*m_VAO, *m_PlaneShader, 6);
	}

	void TestBlinnPhong::OnImGuiRender()
	{
		if (ImGui::RadioButton("BlinnPhong", m_Blinn))
			m_Blinn = true;

		if (ImGui::RadioButton("Phong", !m_Blinn))
			m_Blinn = false;

		ImGui::Spacing();
		ImGui::SliderFloat("Ambient Strength", &m_AmbientStrength, 0.0, 1.0);
		ImGui::SliderFloat("Specular Strength", &m_SpecularStrength, 0.0, 1.0);
		ImGui::SliderFloat("Shininess Factor", &m_Shininess, 0.0, 128.0);
	}
}