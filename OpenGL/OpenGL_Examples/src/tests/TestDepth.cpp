#include "TestDepth.h"

namespace test {
	TestDepth::TestDepth()
	{
	}

	TestDepth::~TestDepth()
	{
		glDisable(GL_DEPTH_TEST);
	}

	void TestDepth::OnUpdate(GLFWwindow* window, float deltaTime, Camera& camera)
	{
	}

	void TestDepth::OnRender()
	{
	}

	void TestDepth::OnImGuiRender()
	{
	}
}