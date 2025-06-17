#pragma once

#include "Test.h"

namespace test {
	class TestExploding : public Test
	{
	private:
		std::unique_ptr<Model> m_Model;
		std::unique_ptr<Shader> m_ObjectShader;
		std::unique_ptr<Shader> m_NormalsShader;

		glm::mat4 m_View;
		float m_FoV;
	public:
		TestExploding();
		~TestExploding();

		void OnUpdate(GLFWwindow* window, float deltaTime, Camera& camera) override;
		void OnRender() override;
	};
}