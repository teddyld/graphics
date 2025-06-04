#pragma once

#include "Test.h"

namespace test {
	class TestLighting : public Test
	{
	private:
		glm::mat4 m_View;
		glm::vec3 m_ViewPos;
		float m_FoV;

		float m_AmbientStrength;
		float m_SpecularStrength;
		int m_Shininess;
		float m_LightColor[3];
		int m_ShaderType;

		std::unique_ptr<VertexArray> m_ObjectVAO;
		std::unique_ptr<VertexArray> m_LightVAO;
		std::unique_ptr<VertexBuffer> m_VBO;

		std::unique_ptr<Shader> m_ObjectShader;
		std::unique_ptr<Shader> m_LightShader;

		std::unique_ptr<Texture> m_Container;
		std::unique_ptr<Texture> m_Glowstone;
	public:
		TestLighting();
		~TestLighting();

		void OnUpdate(GLFWwindow* window, float deltaTime, Camera& camera) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};
}