#pragma once

#include "Test.h"

namespace test {
	class TestExploding : public Test
	{
	private:
		std::unique_ptr<Model> m_Model;
		std::unique_ptr<Shader> m_ObjectShader;
		std::unique_ptr<Shader> m_NormalsShader;

		CameraTransformMatrices m_Transforms;
	public:
		TestExploding();
		~TestExploding();

		void OnUpdate(GLFWwindow* window, float deltaTime, Camera& camera) override;
		void OnRender() override;
	};
}