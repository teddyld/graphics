#pragma once

#include "Test.h"

namespace test {
	class TestHDR : public Test
	{
	private:
		// Light object
		std::unique_ptr<VertexArray> m_CubeVAO;
		std::unique_ptr<VertexBuffer> m_CubeVBO;
		std::unique_ptr<Texture> m_Texture;
		std::unique_ptr<Shader> m_CubeShader;

		// HDR quad
		std::unique_ptr<VertexArray> m_QuadVAO;
		std::unique_ptr<VertexBuffer> m_QuadVBO;
		std::unique_ptr<IndexBuffer> m_QuadEBO;

		std::unique_ptr<FrameBuffer> m_FBO;
		std::unique_ptr<RenderBuffer> m_RBO;
		std::unique_ptr<Shader> m_HDRShader;

		CameraTransformMatrices m_Transforms;

		bool m_EnableHDR;
		float m_Exposure;
	public:
		TestHDR();
		~TestHDR();

		void OnUpdate(GLFWwindow* window, float deltaTime, Camera& camera) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};
}