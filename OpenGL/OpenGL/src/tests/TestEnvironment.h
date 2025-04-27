#pragma once

#include "Test.h"

namespace test {
	class TestEnvironment : public Test
	{
	public:
		TestEnvironment();
		~TestEnvironment();

		void OnRender() override;
		void OnImGuiRender() override;
	};
}