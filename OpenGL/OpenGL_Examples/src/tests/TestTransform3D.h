#pragma once

#include "Test.h"

namespace test {
	class TestTransform3D : public Test
	{
	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_TextureGrassBottom;

		CameraTransformMatrices m_Transforms;
		glm::vec3 m_CubePositions[10];
	public:
		TestTransform3D();
		~TestTransform3D();

		void OnUpdate(GLFWwindow* window, float deltaTime, Camera& camera) override;
		void OnRender() override;
	};
}