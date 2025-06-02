#pragma once

#include "Test.h"
#include "Model.h"

namespace test {
	class TestModel : public Test
	{
	private:
		glm::mat4 m_View;
		float m_FoV;

		std::unique_ptr<Model> m_Model;
		std::unique_ptr<Shader> m_Shader;
	public:
		TestModel();
		~TestModel();

		void OnUpdate(GLFWwindow* window, float deltaTime, Camera* camera) override;
		void OnRender() override;
	};
}