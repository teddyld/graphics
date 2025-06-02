#include "TestModel.h"

namespace test {
	TestModel::TestModel()
	{
		m_Model = std::make_unique<Model>("res/objects/backpack/backpack.obj");
		m_Shader = std::make_unique<Shader>("res/shaders/Model.shader");
	}

	TestModel::~TestModel()
	{
		glDisable(GL_DEPTH_TEST);
	}

	void TestModel::OnUpdate(GLFWwindow* window, float deltaTime, Camera* camera)
	{
		camera->CameraInput(window, deltaTime);
		m_View = camera->GetLookAt();
		m_FoV = camera->GetZoom();
	}

	void TestModel::OnRender()
	{
		glEnable(GL_DEPTH_TEST);

		glm::mat4 projection = glm::perspective(m_FoV, 960.0f / 540.0f, 0.1f, 100.0f);
		glm::mat4 model = glm::mat4(1.0f);

		m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_Model", model);
		m_Shader->SetUniformMat4f("u_View", m_View);
		m_Shader->SetUniformMat4f("u_Projection", projection);

		m_Model->Draw(*m_Shader);
	}
}