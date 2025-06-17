#pragma once

#include "Test.h"

namespace test {
	class TestGeometry : public Test
	{
	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<Shader> m_Shader;
	public:
		TestGeometry();
		~TestGeometry();

		void OnRender() override;
	};
}