#pragma once

#include "Test.h"

namespace test {
	class TestDepth : public Test
	{
	private:
		std::unique_ptr<VertexArray> m_CubeVAO;
		std::unique_ptr<VertexBuffer> m_CubeVBO;
		std::unique_ptr<VertexArray> m_PlaneVAO;
		std::unique_ptr<VertexBuffer> m_PlaneVBO;

		std::unique_ptr<Shader> m_Shader;

		CameraTransformMatrices m_Transforms;
		int m_DepthFunc;
	public:
		TestDepth();
		~TestDepth();

		void OnUpdate(GLFWwindow* window, float deltaTime, Camera& camera) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};
}