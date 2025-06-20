#pragma once

#include "Test.h"

/*
Instancing is a technique where we draw many (mesh data) objects with a single render call
saving us all the CPU->GPU communications each time we need to render an object like telling the GPU
which buffer to read data from, where to find vertex attributes etc.
*/
namespace test {
	class TestInstancing : public Test {
	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<VertexBuffer> m_InstanceVBO;
		std::unique_ptr<Shader> m_Shader;
	public:
		TestInstancing();
		~TestInstancing();

		void OnRender() override;
	};
}