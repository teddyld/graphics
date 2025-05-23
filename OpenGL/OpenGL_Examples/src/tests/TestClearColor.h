#pragma once

#include "Test.h"

namespace test {
	class TestClearColor : public Test
	{
	private:
		float m_ClearColor[4];
	public:
		TestClearColor();
		~TestClearColor();

		void OnRender() override;
		void OnImGuiRender() override;
	};
}