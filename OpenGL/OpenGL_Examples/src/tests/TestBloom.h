#pragma once

#include "Test.h"

namespace test {
	class TestBloom : public Test
	{
	private:
		std::unique_ptr<VertexArray> m_CubeVAO;
		std::unique_ptr<VertexBuffer> m_CubeVBO;
		std::unique_ptr<Texture> m_CubeTexture;
		std::unique_ptr<Shader> m_CubeShader;

		// HDR quad
		std::unique_ptr<VertexArray> m_QuadVAO;
		std::unique_ptr<VertexBuffer> m_QuadVBO;
		std::unique_ptr<IndexBuffer> m_QuadEBO;

		std::unique_ptr<FrameBuffer> m_BloomFBO;
		std::unique_ptr<RenderBuffer> m_RBO;
		std::unique_ptr<Shader> m_HDRShader;

		// Lights
		std::unique_ptr<Shader> m_LightShader;

		// Two-pass Gaussian blur
		std::unique_ptr<FrameBuffer> m_BlurFBO1;
		std::unique_ptr<FrameBuffer> m_BlurFBO2;
		std::unique_ptr<Shader> m_BlurShader;

		CameraTransformMatrices m_Transforms;

		bool m_EnableBloom;
	public:
		TestBloom();
		~TestBloom();

		void OnUpdate(GLFWwindow* window, float deltaTime, Camera& camera) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};
}