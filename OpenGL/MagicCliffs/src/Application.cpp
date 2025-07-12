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
#include "FrameBuffer.h"
#include "RenderBuffer.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Entity/Fox.h"
#include "Environment/Landscape.h"

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
	window = glfwCreateWindow(768, 453, "Magic Cliff", nullptr, nullptr);
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

	Renderer renderer;

	float deltaTime = 0.0f;	// Time between current frame and last frame
	float lastFrame = 0.0f; // Time of last frame

	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::ortho(0.0f, 512.0f, 0.0f, 302.0f, -1.0f, 1.0f);

	Fox fox;
	Landscape landscape;

	float waterVertices[] = {
		0.0f, 0.0f, 0.6f, 0.0f, 0.0f,
		512.0f, 0.0f, 0.6f, 1.0f, 0.0f,
		512.0f, 96.0f, 0.6f, 1.0f, 0.65f,
		0.0f, 96.0f, 0.6f, 0.0f, 0.65f,
	};

	unsigned int indices[] = {
		0, 1, 2, 2, 3, 0
	};

	VertexArray waterVAO;
	IndexBuffer waterEBO(indices, 6);
	VertexBuffer waterVBO(waterVertices, 4 * 5 * sizeof(float), GL_STATIC_DRAW);

	VertexBufferLayout layout;
	layout.Push(GL_FLOAT, 3, GL_FALSE);
	layout.Push(GL_FLOAT, 2, GL_FALSE);
	waterVAO.AddBuffer(waterVBO, layout);

	waterVAO.Unbind();
	waterVBO.Unbind();
	waterEBO.Unbind();

	Texture waterNormal("res/textures/magic_cliffs/environment/water_normal.png");
	Shader waterShader("res/shaders/Water.shader");
	waterShader.Bind();
	waterShader.SetUniform1f("u_Strength", 0.02f);
	waterShader.SetUniform1i("u_Texture", 0);
	waterShader.SetUniform1i("u_Normal", 1);

	glm::vec2 offset = glm::vec2(0.0f, 0.0f);
	float speed = 0.05f;

	glm::mat4 waterModel = glm::translate(glm::mat4(1.0f), glm::vec3(5.0f, -15.0f, 0.0f));

	waterShader.SetUniformMat4f("u_MVP", projection * view * waterModel);
	waterShader.Unbind();

	float screenVertices[] = {
		0.0f, 0.0f, 0.0f, 0.0f,
		512.0f, 0.0f, 1.0f, 0.0f,
		512.0f, 302.0f, 1.0f, 1.0f,
		0.0f,  302.0f, 0.0f, 1.0f,
	};

	VertexArray screenVAO;
	IndexBuffer screenEBO(indices, 6);
	VertexBuffer screenVBO(screenVertices, 4 * 4 * sizeof(float), GL_STATIC_DRAW);

	VertexBufferLayout screenLayout;
	screenLayout.Push(GL_FLOAT, 2, GL_FALSE);
	screenLayout.Push(GL_FLOAT, 2, GL_FALSE);
	screenVAO.AddBuffer(screenVBO, screenLayout);

	screenVAO.Unbind();
	screenVBO.Unbind();
	screenVBO.Unbind();

	Shader screenShader("res/shaders/Screen.shader");
	screenShader.Bind();
	screenShader.SetUniform1i("u_Texture", 0);
	screenShader.SetUniformMat4f("u_MVP", projection);

	FrameBuffer fbo(758, 453, GL_TEXTURE_2D);
	fbo.AttachTexture1i();

	RenderBuffer rbo(758, 453);
	rbo.Configure();
	rbo.AttachBuffer();

	fbo.Unbind();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Render reflected objects to frame buffer
		fbo.Bind();
		renderer.Clear();
		glEnable(GL_DEPTH_TEST);

		landscape.OnRender(view, projection);
		fox.OnRender(view, projection);
		fox.OnUpdate(deltaTime);

		fbo.Unbind();

		// Render water shader using current frame buffer
		fbo.BindTexture(0);
		waterNormal.Bind(1);
		waterShader.Bind();

		offset += glm::vec2(1.0f, 0.0f) * deltaTime * speed;

		waterShader.SetUniform2f("u_Offset", offset.x, offset.y);

		fbo.Bind();

		// Render water to frame buffer
		renderer.Draw(waterVAO, waterEBO, waterShader);

		fbo.Unbind();

		// Render screen-space quad
		renderer.Clear();
		glDisable(GL_DEPTH_TEST);
		fbo.BindTexture(0);
		renderer.Draw(screenVAO, screenEBO, screenShader);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}