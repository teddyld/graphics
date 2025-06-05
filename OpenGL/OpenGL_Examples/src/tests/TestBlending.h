#pragma once

#include "Test.h"

namespace test {
	class TestBlending : public Test
	{
	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<Shader> m_Shader;

		glm::mat4 m_View;
		float m_FoV;
	public:
		TestBlending();
		~TestBlending();

		void OnUpdate(GLFWwindow* window, float deltaTime, Camera& camera) override;
		void OnRender() override;
	};
}