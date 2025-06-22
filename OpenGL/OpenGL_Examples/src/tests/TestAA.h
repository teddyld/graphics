#pragma once

#include "Test.h"

namespace test {
	class TestAA : public Test
	{
	private:
		std::unique_ptr<VertexArray> m_CubeVAO;
		std::unique_ptr<VertexBuffer> m_CubeVBO;

		std::unique_ptr<VertexArray> m_QuadVAO;
		std::unique_ptr<VertexBuffer> m_QuadVBO;

		std::unique_ptr<Shader> m_CubeShader;
		std::unique_ptr<Shader> m_ScreenShader;

		std::unique_ptr<FrameBuffer> m_FBO;
		std::unique_ptr<FrameBuffer> m_IntermediateFBO;
		std::unique_ptr<RenderBuffer> m_RBO;

		CameraTransformMatrices m_Transforms;
		int m_Samples;
	public:
		TestAA();
		~TestAA();

		void OnUpdate(GLFWwindow* window, float deltaTime, Camera& camera) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};
}