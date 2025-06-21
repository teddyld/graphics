#pragma once

#include "Test.h"

namespace test {
	class TestAsteroids : public Test {
	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VBO;

		std::unique_ptr<Model> m_RockObj;
		std::unique_ptr<Model> m_PlanetObj;
		std::unique_ptr<Shader> m_InstanceShader;
		std::unique_ptr<Shader> m_PlanetShader;

		CameraTransformMatrices m_Transforms;

		unsigned int m_Amount;
	public:
		TestAsteroids();
		~TestAsteroids();

		void OnUpdate(GLFWwindow* window, float deltaTime, Camera& camera) override;
		void OnRender() override;
	};
}