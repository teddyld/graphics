#pragma once

#include "Test.h"

namespace test {
	class TestModel : public Test
	{
	private:
		std::unique_ptr<Model> m_Model;
		std::unique_ptr<Shader> m_Shader;

		CameraTransformMatrices m_Transforms;
	public:
		TestModel();
		~TestModel();

		void OnUpdate(GLFWwindow* window, float deltaTime, Camera& camera) override;
		void OnRender() override;
	};
}