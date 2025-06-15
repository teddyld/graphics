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

#include "Camera.h"

struct Vertex2D
{
	glm::vec2 positions;
	glm::vec2 texCoords;
	float texIndex;
};

static Vertex2D* CreateQuad(Vertex2D* target, float x, float y, float textureIndex)
{
	float size = 100.0f;

	target->positions = { x, y };
	target->texCoords = { 0.0f, 0.0f };
	target->texIndex = textureIndex;
	target++;

	target->positions = { x + size, y };
	target->texCoords = { 1.0f, 0.0f };
	target->texIndex = textureIndex;
	target++;

	target->positions = { x + size, y + size };
	target->texCoords = { 1.0f, 1.0f };
	target->texIndex = textureIndex;
	target++;

	target->positions = { x, y + size };
	target->texCoords = { 0.0f, 1.0f };
	target->texIndex = textureIndex;
	target++;

	return target;
}

namespace test {
	class Test
	{
	public:
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
		std::vector<std::pair<std::string, std::function<Test* ()>>> m_Tests;
	public:
		TestMenu(Test*& currentTestPointer);

		void OnImGuiRender() override;

		template<typename T>
		void RegisterTest(const std::string& name)
		{
			std::cout << "Registering test: " << name << std::endl;
			m_Tests.push_back(std::make_pair(name, []() { return new T(); }));
		}
	};
}