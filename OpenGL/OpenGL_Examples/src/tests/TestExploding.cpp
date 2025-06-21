#include "TestExploding.h"

namespace test {
	TestExploding::TestExploding()
	{
		m_Model = std::make_unique<Model>("res/objects/backpack/backpack.obj");
		m_ObjectShader = std::make_unique<Shader>("res/shaders/geometry/Exploding.shader");
		m_NormalsShader = std::make_unique<Shader>("res/shaders/geometry/DisplayNormals.shader");
	}

	TestExploding::~TestExploding()
	{
		glDisable(GL_DEPTH_TEST);
	}

	void TestExploding::OnUpdate(GLFWwindow* window, float deltaTime, Camera& camera)
	{
		camera.CameraInput(window, deltaTime);
		m_Transforms = camera.GetTransformMatrices();
	}

	void TestExploding::OnRender()
	{
		glEnable(GL_DEPTH_TEST);

		glm::mat4 projection = m_Transforms.projection;
		glm::mat4 view = m_Transforms.view;
		glm::mat4 model = glm::mat4(1.0f);

		m_ObjectShader->Bind();
		m_ObjectShader->SetUniformMat4f("u_Model", model);
		m_ObjectShader->SetUniformMat4f("u_View", view);
		m_ObjectShader->SetUniformMat4f("u_Projection", projection);

		m_ObjectShader->SetUniform1f("u_Time", (float)glfwGetTime());

		m_Model->Draw(*m_ObjectShader);

		m_NormalsShader->Bind();
		m_NormalsShader->SetUniformMat4f("u_Model", model);
		m_NormalsShader->SetUniformMat4f("u_View", view);
		m_NormalsShader->SetUniformMat4f("u_Projection", projection);

		// Shows the normal of the object (giving an almost fur-like quality)
		m_Model->Draw(*m_NormalsShader);
	}
}