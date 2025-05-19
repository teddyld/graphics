#pragma once

#include "Test.h"

namespace test {
	class TestShaders : public Test
	{
	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<IndexBuffer> m_EBO;
		std::unique_ptr<Shader> m_Shader;
	public:
		TestShaders();

		void OnUpdate(GLFWwindow* window, float deltaTime, Camera* camera) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};
}