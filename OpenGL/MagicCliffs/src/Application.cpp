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

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(960, 540, "OpenGL", nullptr, nullptr);
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

	Renderer renderer;

	float deltaTime = 0.0f;	// Time between current frame and last frame
	float lastFrame = 0.0f; // Time of last frame

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		renderer.Clear();

		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}