#pragma once

#include "Test.h"

namespace test {
	class TestStencil : public Test
	{
	private:
		std::unique_ptr<VertexArray> m_CubeVAO;
		std::unique_ptr<VertexBuffer> m_CubeVBO;
		std::unique_ptr<VertexArray> m_PlaneVAO;
		std::unique_ptr<VertexBuffer> m_PlaneVBO;

		std::unique_ptr<Texture> m_CubeTexture;
		std::unique_ptr<Texture> m_PlaneTexture;

		std::unique_ptr<Shader> m_TextureShader;
		std::unique_ptr<Shader> m_OutlineShader;

		glm::mat4 m_View;
		float m_FoV;
	public:
		TestStencil();
		~TestStencil();

		void OnUpdate(GLFWwindow* window, float deltaTime, Camera& camera) override;
		void OnRender() override;
	};
}