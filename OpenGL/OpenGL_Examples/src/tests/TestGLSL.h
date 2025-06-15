#pragma once

#include "Test.h"

namespace test {
	class TestGLSL : public Test
	{
	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<Shader> m_RedShader;
		std::unique_ptr<Shader> m_GreenShader;
		std::unique_ptr<Shader> m_BlueShader;
		std::unique_ptr<Shader> m_YellowShader;

		std::unique_ptr<UniformBuffer> m_UniformBuffer;

		glm::mat4 m_View;
		float m_FoV;
	public:
		TestGLSL();
		~TestGLSL();

		void OnUpdate(GLFWwindow* window, float deltaTime, Camera& camera) override;
		void OnRender() override;
	};
}