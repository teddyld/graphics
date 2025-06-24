#pragma once

#include "Test.h"

namespace test {
	class TestGammaCorrection : public Test
	{
	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VBO;

		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_GammaCorrectedTexture;
		std::unique_ptr<Texture> m_Texture;

		CameraTransformMatrices m_Transforms;
		glm::vec3 m_ViewPos;

		bool m_GammaCorrection;
		float m_Gamma;
		bool m_Attenuation;
	public:
		TestGammaCorrection();
		~TestGammaCorrection();

		void OnUpdate(GLFWwindow* window, float deltaTime, Camera& camera) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};
}