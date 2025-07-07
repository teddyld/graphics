#pragma once

#include "Test.h"

namespace test {
	class TestNormalMapping : public Test
	{
	private:
		std::unique_ptr<VertexArray> m_PlaneVAO;
		std::unique_ptr<VertexBuffer> m_PlaneVBO;
		std::unique_ptr<Texture> m_PlaneDiffuse;
		std::unique_ptr<Texture> m_PlaneNormalMap;
		std::unique_ptr<Shader> m_PlaneShader;

		std::unique_ptr<VertexArray> m_LightVAO;
		std::unique_ptr<VertexBuffer> m_LightVBO;
		std::unique_ptr<Texture> m_LightDiffuse;
		std::unique_ptr<Shader> m_LightShader;

		CameraTransformMatrices m_Transforms;
		glm::vec3 m_ViewPos;
	public:
		TestNormalMapping();
		~TestNormalMapping();

		void OnUpdate(GLFWwindow* window, float deltaTime, Camera& camera) override;
		void OnRender() override;
	};
}