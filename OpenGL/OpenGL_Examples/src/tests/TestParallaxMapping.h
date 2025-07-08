#pragma once

#include "Test.h"

namespace test {
	class TestParallaxMapping : public Test
	{
	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<Texture> m_Diffuse;
		std::unique_ptr<Texture> m_NormalMap;
		std::unique_ptr<Texture> m_ParallaxMap;
		std::unique_ptr<Shader> m_Shader;

		CameraTransformMatrices m_Transforms;
		glm::vec3 m_ViewPos;

		int m_Selected;
		int m_MinLayers;
		int m_MaxLayers;
	public:
		TestParallaxMapping();
		~TestParallaxMapping();

		void OnUpdate(GLFWwindow* window, float deltaTime, Camera& camera) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};
}