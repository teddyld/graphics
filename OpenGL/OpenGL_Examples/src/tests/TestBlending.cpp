#include "TestBlending.h"

namespace test {
	TestBlending::TestBlending()
	{
	}

	TestBlending::~TestBlending()
	{
		glDisable(GL_DEPTH_TEST);
	}

	void TestBlending::OnUpdate(GLFWwindow* window, float deltaTime, Camera& camera)
	{
		camera.CameraInput(window, deltaTime);
		m_View = camera.GetLookAt();
		m_FoV = camera.GetZoom();
	}

	void TestBlending::OnRender()
	{
	}
}