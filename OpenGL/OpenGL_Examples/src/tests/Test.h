#pragma once
#include <string>
#include <functional>
#include <iostream>
#include <vector>
#include <memory>
#include <array>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "imgui/imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Texture.h"
#include "Renderer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "Model.h"
#include "UniformBuffer.h"
#include "FrameBuffer.h"
#include "RenderBuffer.h"

#include "Camera.h"

namespace test {
	class Test
	{
	public:
		int SCR_WIDTH = 1920;
		int SCR_HEIGHT = 1080;

		Test() {}
		virtual ~Test() {}

		virtual void OnUpdate(GLFWwindow* window, float deltaTime, Camera& camera) {};
		virtual void OnRender() {};
		virtual void OnImGuiRender() {};
	};

	class TestMenu : public Test
	{
	private:
		Test*& m_CurrentTest;
		std::vector<std::tuple<std::string, std::string, std::function<Test* ()>>> m_Tests;
		std::string m_CurrentGroup;
	public:
		TestMenu(Test*& currentTestPointer);

		void OnImGuiRender() override;

		template<typename T>
		void RegisterTest(const std::string& name)
		{
			std::cout << "Registering test: " << name << std::endl;
			m_Tests.push_back(std::tuple(name, m_CurrentGroup, []() { return new T(); }));
		}

		void RegisterGroup(const std::string& name)
		{
			m_CurrentGroup = name;
		}
	};
}