#pragma once

#include "Test.h"

namespace test {
	enum EnvironmentMapping {
		REFLECTIVE = 0, REFRACTION = 1
	};

	class TestCubemaps : public Test
	{
	private:
		std::unique_ptr<VertexArray> m_ObjectVAO;
		std::unique_ptr<VertexBuffer> m_ObjectVBO;
		std::unique_ptr<Shader> m_ReflectiveShader;
		std::unique_ptr<Shader> m_RefractiveShader;

		std::unique_ptr<VertexArray> m_SkyboxVAO;
		std::unique_ptr<VertexBuffer> m_SkyboxVBO;
		std::unique_ptr<Texture> m_SkyboxTexture;
		std::unique_ptr<Shader> m_SkyboxShader;

		glm::mat4 m_View;
		float m_FoV;
		glm::vec3 m_CameraPos;

		EnvironmentMapping m_EnvironmentMapping;
		int m_From;
		int m_To;
		float m_RefractiveIndex;
	public:
		TestCubemaps();
		~TestCubemaps();

		void OnUpdate(GLFWwindow* window, float deltaTime, Camera& camera) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};
}