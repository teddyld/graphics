#pragma once
#pragma once

#include "Test.h"

namespace test {
	class TestMaterial : public Test
	{
	private:
		glm::mat4 m_View;
		float m_FoV;

		glm::vec3 m_ViewPos;

		std::unique_ptr<VertexArray> m_ContainerVAO;
		std::unique_ptr<VertexArray> m_LightVAO;
		std::unique_ptr<VertexBuffer> m_VBO;

		std::unique_ptr<Shader> m_ContainerShader;
		std::unique_ptr<Shader> m_LightShader;

		std::unique_ptr<Texture> m_ContainerDiffuse;
		std::unique_ptr<Texture> m_ContainerSpecular;
		std::unique_ptr<Texture> m_ContainerEmission;
		std::unique_ptr<Texture> m_LightTexture;
	public:
		TestMaterial();
		~TestMaterial();

		void OnRender() override;
		void OnUpdate(GLFWwindow* window, float deltaTime, Camera& camera) override;
		void OnImGuiRender() override;
	};
}