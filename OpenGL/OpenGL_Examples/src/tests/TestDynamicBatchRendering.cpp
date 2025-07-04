#include "TestDynamicBatchRendering.h"
#include <iostream>

namespace test {
	TestDynamicBatchRendering::TestDynamicBatchRendering()
		: m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))), m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)), m_QuadPosition{ 120.0f, 120.0f }, m_NumQuadsBear(0)
	{
		m_VAO = std::make_unique<VertexArray>();
		m_VBO = std::make_unique<VertexBuffer>(nullptr, sizeof(Vertex2D) * 1000, GL_DYNAMIC_DRAW);

		VertexBufferLayout layout;
		layout.Push(GL_FLOAT, 2, GL_FALSE);
		layout.Push(GL_FLOAT, 2, GL_FALSE);
		layout.Push(GL_FLOAT, 1, GL_FALSE);
		m_VAO->AddBuffer(*m_VBO, layout);

		m_TextureBear = std::make_unique<Texture>("res/textures/bear.png");
		m_TextureMaple = std::make_unique<Texture>("res/textures/maple.png");

		m_Shader = std::make_unique<Shader>("res/shaders/Texture16.shader");
		m_Shader->Bind();

		int samplers[2] = { 0, 1 };

		m_Shader->SetUniform1iv("u_Textures", 2, samplers);

		glm::mat4 mvp = m_Proj * m_View;
		m_Shader->SetUniformMat4f("u_MVP", mvp);

		m_VAO->Unbind();
		m_VBO->Unbind();
		m_Shader->Unbind();
	}

	Vertex2D* TestDynamicBatchRendering::CreateQuad(Vertex2D* target, float x, float y, float textureIndex)
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

	void TestDynamicBatchRendering::OnRender()
	{
		Renderer renderer;

		m_VAO->Bind();
		m_TextureBear->Bind(0);
		m_TextureMaple->Bind(1);

		std::array<Vertex2D, 1000> vertices;
		std::vector<unsigned int> indices;

		Vertex2D* buffer = vertices.data();

		buffer = CreateQuad(buffer, 320.0f, 120.0f, 1.0f);

		for (int i = 0; i < m_NumQuadsBear + 1; i++)
		{
			indices.push_back(i * 4);
			indices.push_back(1 + i * 4);
			indices.push_back(2 + i * 4);
			indices.push_back(2 + i * 4);
			indices.push_back(3 + i * 4);
			indices.push_back(i * 4);

			buffer = CreateQuad(buffer, m_QuadPosition[0] + 10.0f * i, m_QuadPosition[1] + 10.0f * i, 0.0f);
		}

		m_EBO = std::make_unique<IndexBuffer>(&indices[0], (m_NumQuadsBear + 1) * 6);
		m_VBO->UpdateBufferSubData(0, sizeof(Vertex2D) * vertices.size(), vertices.data());

		renderer.Draw(*m_VAO, *m_EBO, *m_Shader);
	}

	void TestDynamicBatchRendering::OnImGuiRender()
	{
		ImGui::DragFloat2("Quad Position", m_QuadPosition, 0.1f);
		ImGui::SliderInt("Number of Quads - Bear", &m_NumQuadsBear, 0, 100);
	}
}