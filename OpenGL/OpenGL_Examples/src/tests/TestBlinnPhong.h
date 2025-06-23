#pragma once

#include "Test.h"

namespace test {
	class TestBlinnPhong : public Test
	{
	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<Shader> m_PlaneShader;
		std::unique_ptr<Texture> m_Texture;

		CameraTransformMatrices m_Transforms;
		glm::vec3 m_ViewPos;

		bool m_Blinn;

		float m_AmbientStrength;
		float m_SpecularStrength;
		float m_Shininess;
		float m_LightColor[3];
	public:
		TestBlinnPhong();
		~TestBlinnPhong();

		void OnUpdate(GLFWwindow* window, float deltaTime, Camera& camera) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};
}