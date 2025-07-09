#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "tests/Test.h"
#include "tests/TestClearColor.h"
#include "tests/TestTexture2D.h"
#include "tests/TestBatchRendering.h"
#include "tests/TestDynamicBatchRendering.h"
#include "tests/TestTransform3D.h"
#include "tests/TestChangeTexture.h"
#include "tests/TestShaders.h"
#include "tests/TestLighting.h"
#include "tests/TestMaterial.h"
#include "tests/TestLightCasters.h"
#include "tests/TestModel.h"
#include "tests/TestDepth.h"
#include "tests/TestStencil.h"
#include "tests/TestBlending.h"
#include "tests/TestCubemaps.h"
#include "tests/TestGLSL.h"
#include "tests/TestGeometry.h"
#include "tests/TestExploding.h"
#include "tests/TestInstancing.h"
#include "tests/TestAsteroids.h"
#include "tests/TestAA.h"
#include "tests/TestBlinnPhong.h"
#include "tests/TestGammaCorrection.h"
#include "tests/TestShadowMapping.h"
#include "tests/TestNormalMapping.h"
#include "tests/TestParallaxMapping.h"
#include "tests/TestHDR.h"

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	window = glfwCreateWindow(mode->width, mode->height, "OpenGL", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	// Enable vsync
	glfwSwapInterval(1);

	/* Get access to modern OpenGL functionality */
	if (glewInit() != GLEW_OK)
		std::cout << "Error!" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;

	// Setup Dear ImGui context
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer back ends
	ImGui_ImplGlfw_InitForOpenGL(window, true);

	ImGui_ImplOpenGL3_Init((char*)glGetString(330));

	test::Test* currentTest = nullptr;
	test::TestMenu* testMenu = new test::TestMenu(currentTest);
	currentTest = testMenu;

	testMenu->RegisterGroup("Basic");
	testMenu->RegisterTest<test::TestClearColor>("Clear Color");
	testMenu->RegisterTest<test::TestShaders>("Exploring shaders");
	testMenu->RegisterTest<test::TestTexture2D>("Texture 2D");
	testMenu->RegisterTest<test::TestChangeTexture>("Changing textures dynamically");
	testMenu->RegisterTest<test::TestTransform3D>("A 3D scene");
	testMenu->RegisterGroup("Batching");
	testMenu->RegisterTest<test::TestBatchRendering>("Batch Rendering");
	testMenu->RegisterTest<test::TestDynamicBatchRendering>("Dynamic Batch Rendering");
	testMenu->RegisterGroup("Lighting");
	testMenu->RegisterTest<test::TestLighting>("Simple Lighting Types");
	testMenu->RegisterTest<test::TestMaterial>("Materials");
	testMenu->RegisterTest<test::TestLightCasters>("Light casting: directional, point, and area");
	testMenu->RegisterGroup("Model Loading");
	testMenu->RegisterTest<test::TestModel>("Model loading: Backpack");
	testMenu->RegisterGroup("Advanced OpenGL");
	testMenu->RegisterTest<test::TestDepth>("Depth testing");
	testMenu->RegisterTest<test::TestStencil>("Object outlining using stencil testing");
	testMenu->RegisterTest<test::TestBlending>("Blending testing");
	testMenu->RegisterTest<test::TestCubemaps>("Skyboxes using cubemaps");
	testMenu->RegisterTest<test::TestGLSL>("Advanced GLSL using the uniform buffer");
	testMenu->RegisterTest<test::TestGeometry>("Geometry shader");
	testMenu->RegisterTest<test::TestExploding>("Exploding shader");
	testMenu->RegisterTest<test::TestInstancing>("Instancing objects");
	testMenu->RegisterTest<test::TestAsteroids>("Asteroids using instancing");
	testMenu->RegisterTest<test::TestAA>("Anti Aliasing techniques");
	testMenu->RegisterGroup("Advanced Lighting");
	testMenu->RegisterTest<test::TestBlinnPhong>("Blinn-Phong lighting model");
	testMenu->RegisterTest<test::TestGammaCorrection>("Gamma correction");
	testMenu->RegisterTest<test::TestShadowMapping>("Shadow mapping");
	testMenu->RegisterTest<test::TestNormalMapping>("Normal mapping");
	testMenu->RegisterTest<test::TestParallaxMapping>("Parallax mapping");
	testMenu->RegisterTest<test::TestHDR>("HDR");

	Renderer renderer;
	Camera camera(glm::vec3(-3.0f, 0.0f, 0.0f), mode->width, mode->height);

	float deltaTime = 0.0f;	// Time between current frame and last frame
	float lastFrame = 0.0f; // Time of last frame

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		renderer.Clear();

		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (currentTest)
		{
			currentTest->OnUpdate(window, deltaTime, camera);
			currentTest->OnRender();
			ImGui::Begin("Test");

			if (currentTest != testMenu && ImGui::Button("<-"))
			{
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				delete currentTest;
				currentTest = testMenu;
				camera.CameraReset();
			}

			currentTest->OnImGuiRender();
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	if (currentTest != testMenu)
		delete testMenu;
	delete currentTest;

	// ImGui Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}