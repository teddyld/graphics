#pragma once

#include "Test.h"

namespace test {
	class TestDepth : public Test
	{
	private:
		std::unique_ptr<VertexArray> m_CubeVAO;
		std::unique_ptr<VertexBuffer> m_CubeVBO;
		std::unique_ptr<VertexArray> m_PlaneVAO;
		std::unique_ptr<VertexBuffer> m_PlaneVBO;

		std::unique_ptr<Shader> m_Shader;

		glm::mat4 m_View;
		float m_FoV;

		int m_DepthFunc;
		std::map<const char*, GLenum> m_Functions = {
			{ "GL_ALWAYS", GL_ALWAYS },
			{ "GL_NEVER", GL_NEVER },
			{ "GL_LESS", GL_LESS },
			{ "GL_EQUAL", GL_EQUAL },
			{ "GL_LEQUAL", GL_LEQUAL },
			{ "GL_GREATER", GL_GREATER },
			{ "GL_NOTEQUAL", GL_NOTEQUAL },
			{ "GL_GEQUAL", GL_GEQUAL }
		};
		std::vector<const char*> m_Options = { "GL_ALWAYS", "GL_NEVER", "GL_LESS", "GL_EQUAL", "GL_LEQUAL", "GL_GREATER", "GL_NOTEQUAL", "GL_GEQUAL" };
	public:
		TestDepth();
		~TestDepth();

		void OnUpdate(GLFWwindow* window, float deltaTime, Camera& camera) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};
}