#pragma once

#include "Test.h"

namespace test {
	class TestDepth : public Test
	{
	private:

	public:
		TestDepth();
		~TestDepth();

		void OnUpdate(GLFWwindow* window, float deltaTime, Camera& camera) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};
}