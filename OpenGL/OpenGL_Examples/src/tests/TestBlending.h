#pragma once

#include "Test.h"

namespace test {
	class TestBlending : public Test
	{
	private:
		std::unique_ptr<VertexArray> m_CubeVAO;
		std::unique_ptr<VertexBuffer> m_CubeVBO;
		std::unique_ptr<VertexArray> m_PlaneVAO;
		std::unique_ptr<VertexBuffer> m_PlaneVBO;
		std::unique_ptr<VertexArray> m_WindowVAO;
		std::unique_ptr<VertexBuffer> m_WindowVBO;
		std::unique_ptr<Shader> m_Shader;

		std::unique_ptr<Texture> m_CubeTexture;
		std::unique_ptr<Texture> m_PlaneTexture;
		std::unique_ptr<Texture> m_WindowTexture;

		glm::mat4 m_View;
		float m_FoV;
		glm::vec3 m_Position;

		std::vector<glm::vec3> m_WindowPos;
	public:
		TestBlending();
		~TestBlending();

		void OnUpdate(GLFWwindow* window, float deltaTime, Camera& camera) override;
		void OnRender() override;
	};
}