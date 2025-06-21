#include "TestGLSL.h"

namespace test {
	TestGLSL::TestGLSL()
	{
		float cubeVertices[] = {
			-0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,

			-0.5f, -0.5f,  0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,

			-0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,

			 0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,

			-0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f, -0.5f,

			-0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f, -0.5f,
		};

		m_VAO = std::make_unique<VertexArray>();
		m_VBO = std::make_unique<VertexBuffer>(cubeVertices, 3 * 36 * sizeof(float), GL_STATIC_DRAW);

		VertexBufferLayout layout;
		layout.Push(GL_FLOAT, 3, GL_FALSE);
		m_VAO->AddBuffer(*m_VBO, layout);

		m_RedShader = std::make_unique<Shader>("res/shaders/advanced_glsl/Red.shader");
		m_GreenShader = std::make_unique<Shader>("res/shaders/advanced_glsl/Green.shader");
		m_BlueShader = std::make_unique<Shader>("res/shaders/advanced_glsl/Blue.shader");
		m_YellowShader = std::make_unique<Shader>("res/shaders/advanced_glsl/Yellow.shader");

		m_UniformBuffer = std::make_unique<UniformBuffer>(2 * sizeof(glm::mat4), GL_STATIC_DRAW);

		m_UniformBuffer->BindBlock(*m_RedShader, "Matrices", 0);
		m_UniformBuffer->BindBlock(*m_GreenShader, "Matrices", 0);
		m_UniformBuffer->BindBlock(*m_BlueShader, "Matrices", 0);
		m_UniformBuffer->BindBlock(*m_YellowShader, "Matrices", 0);

		m_UniformBuffer->BindBufferRange(0, 0, 2 * sizeof(glm::mat4));

		m_VAO->Unbind();
		m_VBO->Unbind();
		m_UniformBuffer->Unbind();
	}

	TestGLSL::~TestGLSL()
	{
		glDisable(GL_DEPTH_TEST);
	}

	void TestGLSL::OnUpdate(GLFWwindow* window, float deltaTime, Camera& camera)
	{
		camera.CameraInput(window, deltaTime);
		m_Transforms = camera.GetTransformMatrices();
	}

	void TestGLSL::OnRender()
	{
		Renderer renderer;
		glEnable(GL_DEPTH_TEST);

		glm::mat4 projection = m_Transforms.projection;
		glm::mat4 view = m_Transforms.view;

		m_UniformBuffer->UpdateBufferSubData(0, sizeof(glm::mat4), &projection);
		m_UniformBuffer->UpdateBufferSubData(sizeof(glm::mat4), sizeof(glm::mat4), &view);

		std::vector<glm::vec3> positions = {
			glm::vec3(-0.75f, 0.75f, 0.0f),
			glm::vec3(0.75f, 0.75f, 0.0f),
			glm::vec3(-0.75f, -0.75f, 0.0f),
			glm::vec3(0.75f, -0.75f, 0.0f)
		};

		m_RedShader->Bind();
		m_RedShader->SetUniformMat4f("u_Model", glm::translate(glm::mat4(1.0f), positions[0]));
		renderer.Draw(*m_VAO, *m_RedShader, 36);

		m_GreenShader->Bind();
		m_GreenShader->SetUniformMat4f("u_Model", glm::translate(glm::mat4(1.0f), positions[1]));
		renderer.Draw(*m_VAO, *m_GreenShader, 36);

		m_BlueShader->Bind();
		m_BlueShader->SetUniformMat4f("u_Model", glm::translate(glm::mat4(1.0f), positions[2]));
		renderer.Draw(*m_VAO, *m_BlueShader, 36);

		m_YellowShader->Bind();
		m_YellowShader->SetUniformMat4f("u_Model", glm::translate(glm::mat4(1.0f), positions[3]));
		renderer.Draw(*m_VAO, *m_YellowShader, 36);
	}
}