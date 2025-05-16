#pragma once

#include "Test.h"

namespace test {
	class TestChangeTexture : public Test
	{
	private:
		glm::mat4 m_View;
		glm::mat4 m_Proj;

		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<IndexBuffer> m_EBO;
		std::unique_ptr<Shader> m_Shader;

		std::vector<std::unique_ptr<Texture>> m_Textures;
		std::unique_ptr<Texture> m_Texture1;
		std::unique_ptr<Texture> m_Texture2;
		std::unique_ptr<Texture> m_Texture3;

		int m_TextureID;
	public:
		TestChangeTexture();

		void OnRender() override;
		void OnImGuiRender() override;
	};
}