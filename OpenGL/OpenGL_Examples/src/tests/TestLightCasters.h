#pragma once

#include "Test.h"

enum LightType
{
	DIRECTIONAL = 0, POINT = 1, SPOT = 2, AREA = 3
};

namespace test {
	class TestLightCasters : public Test
	{
	private:
		glm::mat4 m_View;
		float m_FoV;

		glm::vec3 m_ViewPos;
		glm::vec3 m_ViewFront;

		glm::vec3 m_CubePositions[10];

		int m_LightType;

		std::unique_ptr<VertexArray> m_ContainerVAO;
		std::unique_ptr<VertexArray> m_LightVAO;

		std::unique_ptr<VertexBuffer> m_VBO;

		std::unique_ptr<Texture> m_ContainerDiffuse;
		std::unique_ptr<Texture> m_ContainerSpecular;
		std::unique_ptr<Shader> m_ContainerShader;

		std::unique_ptr<Texture> m_LightTexture;
		std::unique_ptr<Shader> m_LightShader;
	public:
		TestLightCasters();
		~TestLightCasters();

		void OnRender() override;
		void OnUpdate(GLFWwindow* window, float deltaTime, Camera* camera) override;
		void OnImGuiRender() override;
	};
}