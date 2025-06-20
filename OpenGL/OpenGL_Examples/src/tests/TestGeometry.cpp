#include "TestGeometry.h"

namespace test {
	TestGeometry::TestGeometry()
	{
		float points[] = {
			-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // top-left
			 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // top-right
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // bottom-right
			-0.5f, -0.5f, 1.0f, 1.0f, 0.0f, // bottom-left
		};

		m_VAO = std::make_unique<VertexArray>();
		m_VBO = std::make_unique<VertexBuffer>(points, 4 * 5 * sizeof(float), GL_STATIC_DRAW);

		VertexBufferLayout layout;
		layout.Push(GL_FLOAT, 2, GL_FALSE);
		layout.Push(GL_FLOAT, 3, GL_FALSE);
		m_VAO->AddBuffer(*m_VBO, layout);

		m_Shader = std::make_unique<Shader>("res/shaders/Geometry.shader");

		m_VAO->Unbind();
		m_VBO->Unbind();
	}

	TestGeometry::~TestGeometry()
	{
		glDisable(GL_DEPTH_TEST);
	}

	void TestGeometry::OnRender()
	{
		glEnable(GL_DEPTH_TEST);

		m_Shader->Bind();
		m_VAO->Bind();

		glDrawArrays(GL_POINTS, 0, 4);
	}
}