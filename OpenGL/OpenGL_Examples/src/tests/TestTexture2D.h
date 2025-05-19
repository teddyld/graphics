#pragma once
#include "Test.h"

namespace test {
	class TestTexture2D : public Test
	{
	private:
		glm::vec3 m_TranslationA;
		glm::vec3 m_TranslationB;
		glm::mat4 m_View;
		glm::mat4 m_Proj;
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture;
	public:
		TestTexture2D();

		void OnRender() override;
		void OnImGuiRender() override;
	};
}