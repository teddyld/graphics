#include "TestInstancing.h"

namespace test {
	TestInstancing::TestInstancing()
	{
		glm::vec2 translations[100];
		int index = 0;
		float offset = 0.1f;
		for (int y = -10; y < 10; y += 2)
		{
			for (int x = -10; x < 10; x += 2)
			{
				glm::vec2 translation;
				translation.x = (float)x / 10.0f + offset;
				translation.y = (float)y / 10.0f + offset;
				translations[index++] = translation;
			}
		}

		m_InstanceVBO = std::make_unique<VertexBuffer>(&translations[0], 100 * sizeof(glm::vec2), GL_STATIC_DRAW);
		m_InstanceVBO->Unbind();

		float quadVertices[] = {
			// positions     // colors
			-0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
			 0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
			-0.05f, -0.05f,  0.0f, 0.0f, 1.0f,

			-0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
			 0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
			 0.05f,  0.05f,  0.0f, 1.0f, 1.0f
		};

		m_VAO = std::make_unique<VertexArray>();
		m_VBO = std::make_unique<VertexBuffer>(quadVertices, sizeof(quadVertices), GL_STATIC_DRAW);

		VertexBufferLayout layout;
		layout.Push(GL_FLOAT, 2, GL_FALSE);
		layout.Push(GL_FLOAT, 3, GL_FALSE);
		m_VAO->AddBuffer(*m_VBO, layout);

		m_Shader = std::make_unique<Shader>("res/shaders/instancing/Instance2.shader");

		VertexBufferLayout instanceLayout;
		instanceLayout.Push(GL_FLOAT, 2, GL_FALSE);
		m_VAO->AddBufferInstanced(*m_InstanceVBO, instanceLayout, 2);

		m_VAO->Unbind();
		m_VBO->Unbind();
		m_InstanceVBO->Unbind();
	}

	TestInstancing::~TestInstancing()
	{
	}

	void TestInstancing::OnRender()
	{
		Renderer renderer;
		renderer.DrawInstance(*m_VAO, *m_Shader, 6, 100); // 100 triangles of 6 vertices each
	}
}