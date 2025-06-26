#pragma once

#include "Test.h"

namespace test {
	class TestShadowMapping : public Test
	{
	private:
		std::unique_ptr<VertexArray> m_CubeVAO;
		std::unique_ptr<VertexBuffer> m_CubeVBO;

		std::unique_ptr<VertexArray> m_FloorVAO;
		std::unique_ptr<VertexBuffer> m_FloorVBO;

		std::unique_ptr<VertexArray> m_QuadVAO;
		std::unique_ptr<IndexBuffer> m_QuadEBO;
		std::unique_ptr<VertexBuffer> m_QuadVBO;

		std::unique_ptr<FrameBuffer> m_DepthMapFBO;

		std::unique_ptr<Texture> m_CubeTexture;
		std::unique_ptr<Texture> m_FloorTexture;
		std::unique_ptr<Texture> m_LightTexture;

		std::unique_ptr<Shader> m_DepthMapShader;
		std::unique_ptr<Shader> m_DebugQuadShader;
		std::unique_ptr<Shader> m_ShadowShader;
		std::unique_ptr<Shader> m_LightCubeShader;

		CameraTransformMatrices m_Transforms;
		glm::vec3 m_ViewPos;

		int m_Selected;
		glm::vec3 m_LightPos;
	public:
		TestShadowMapping();
		~TestShadowMapping();

		void RenderScene(Shader& shader, bool textured);
		void RenderDepthMap();

		void OnUpdate(GLFWwindow* window, float deltaTime, Camera& camera) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};
}