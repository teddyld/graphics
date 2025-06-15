#pragma once

#include "Test.h"

namespace test {
	class TestDynamicBatchRendering : public Test
	{
	private:
		glm::mat4 m_View;
		glm::mat4 m_Proj;
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<IndexBuffer> m_EBO;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_TextureBear;
		std::unique_ptr<Texture> m_TextureMaple;
		float m_QuadPosition[2];
		int m_NumQuadsBear;
	public:
		TestDynamicBatchRendering();

		void OnRender() override;
		void OnImGuiRender() override;
	};
}