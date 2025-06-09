#include "TestBlending.h"

namespace test {
	TestBlending::TestBlending()
	{
		float cubeVertices[] = {
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

			-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
			 0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
			 0.5f, 0.5f,  0.5f, 1.0f, 0.0f,
			 0.5f, 0.5f,  0.5f, 1.0f, 0.0f,
			-0.5f, 0.5f,  0.5f, 0.0f, 0.0f,
			-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
		};

		float planeVertices[] = {
			 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
			-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
			-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

			 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
			-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
			 5.0f, -0.5f, -5.0f,  2.0f, 2.0f
		};

		float windowVertices[] = {
			0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
			0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
			1.0f, -0.5f,  0.0f,  1.0f,  1.0f,

			0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
			1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
			1.0f,  0.5f,  0.0f,  1.0f,  0.0f
		};

		m_WindowPos.push_back(glm::vec3(-1.5f, 0.0f, -0.48f));
		m_WindowPos.push_back(glm::vec3(1.5f, 0.0f, 0.51f));
		m_WindowPos.push_back(glm::vec3(0.0f, 0.0f, 0.7f));
		m_WindowPos.push_back(glm::vec3(-0.3f, 0.0f, -2.3f));
		m_WindowPos.push_back(glm::vec3(0.5f, 0.0f, -0.6f));

		m_CubeVAO = std::make_unique<VertexArray>();
		m_CubeVBO = std::make_unique<VertexBuffer>(cubeVertices, 36 * 5 * sizeof(float), GL_STATIC_DRAW);

		VertexBufferLayout layout;
		layout.Push(GL_FLOAT, 3, GL_FALSE);
		layout.Push(GL_FLOAT, 2, GL_FALSE);
		m_CubeVAO->AddBuffer(*m_CubeVBO, layout);

		m_PlaneVAO = std::make_unique<VertexArray>();
		m_PlaneVBO = std::make_unique<VertexBuffer>(planeVertices, 6 * 5 * sizeof(float), GL_STATIC_DRAW);
		m_PlaneVAO->AddBuffer(*m_PlaneVBO, layout);

		m_WindowVAO = std::make_unique<VertexArray>();
		m_WindowVBO = std::make_unique<VertexBuffer>(windowVertices, 6 * 5 * sizeof(float), GL_STATIC_DRAW);
		m_WindowVAO->AddBuffer(*m_WindowVBO, layout);

		m_Shader = std::make_unique<Shader>("res/shaders/Texture.shader");
		m_Shader->Bind();
		m_Shader->SetUniform1i("u_Texture", 0);

		std::map<GLenum, GLint> options =
		{
			{ GL_TEXTURE_MIN_FILTER, GL_LINEAR },
			{ GL_TEXTURE_MAG_FILTER, GL_LINEAR },
			{ GL_TEXTURE_WRAP_S, GL_REPEAT },
			{ GL_TEXTURE_WRAP_T, GL_REPEAT },
		};

		m_CubeTexture = std::make_unique<Texture>("res/textures/minecraft/grass_bottom.jpg");
		m_PlaneTexture = std::make_unique<Texture>("res/textures/minecraft/grass_top.jpg", GL_TEXTURE_2D, options);
		m_WindowTexture = std::make_unique<Texture>("res/textures/opengl/blending_transparent_window.png");
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
		m_Position = camera.GetPosition();
	}

	void TestBlending::OnRender()
	{
		Renderer renderer;

		glEnable(GL_DEPTH_TEST);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glm::mat4 projection = glm::perspective(glm::radians(m_FoV), 960.0f / 540.0f, 0.1f, 100.0f);

		m_Shader->Bind();
		m_CubeTexture->Bind(0);

		// Draw opaque objects first
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, -1.0f));
		m_Shader->SetUniformMat4f("u_MVP", projection * m_View * model);
		renderer.Draw(*m_CubeVAO, *m_Shader, 36);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f));
		m_Shader->SetUniformMat4f("u_MVP", projection * m_View * model);
		renderer.Draw(*m_CubeVAO, *m_Shader, 36);

		m_Shader->SetUniformMat4f("u_MVP", projection * m_View);
		m_PlaneTexture->Bind(0);
		renderer.Draw(*m_PlaneVAO, *m_Shader, 6);

		// Sort transparent objects
		m_WindowTexture->Bind(0);
		std::map<float, glm::vec3> sorted;
		for (unsigned int i = 0; i < m_WindowPos.size(); i++)
		{
			float distance = glm::length(m_Position - m_WindowPos[i]);
			sorted[distance] = m_WindowPos[i];
		}

		// Draw transparent objects in sorted order (furthest to closest)
		for (std::map<float, glm::vec3>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); ++it)
		{
			model = glm::translate(glm::mat4(1.0f), it->second);
			m_Shader->SetUniformMat4f("u_MVP", projection * m_View * model);
			renderer.Draw(*m_WindowVAO, *m_Shader, 6);
		}
	}
}