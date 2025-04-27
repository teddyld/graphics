#pragma once

#include "Test.h"

namespace test {
	class TestTeapot : public Test
	{
	public:
		TestTeapot();
		~TestTeapot();

		void OnRender() override;
		void OnImGuiRender() override;
	};
}