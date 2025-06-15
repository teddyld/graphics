#include "TestStencil.h"

namespace test {
	TestStencil::TestStencil()
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
			 5.0f, -0.5f,  5.0f,  8.0f, 0.0f,
			-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
			-5.0f, -0.5f, -5.0f,  0.0f, 8.0f,

			 5.0f, -0.5f,  5.0f,  8.0f, 0.0f,
			-5.0f, -0.5f, -5.0f,  0.0f, 8.0f,
			 5.0f, -0.5f, -5.0f,  8.0f, 8.0f
		};

		m_CubeVAO = std::make_unique<VertexArray>();
		m_CubeVBO = std::make_unique<VertexBuffer>(cubeVertices, 36 * 5 * sizeof(float), GL_STATIC_DRAW);

		VertexBufferLayout layout;
		layout.Push(GL_FLOAT, 3, GL_FALSE);
		layout.Push(GL_FLOAT, 2, GL_FALSE);
		m_CubeVAO->AddBuffer(*m_CubeVBO, layout);

		m_PlaneVAO = std::make_unique<VertexArray>();
		m_PlaneVBO = std::make_unique<VertexBuffer>(planeVertices, 6 * 5 * sizeof(float), GL_STATIC_DRAW);
		m_PlaneVAO->AddBuffer(*m_PlaneVBO, layout);

		m_TextureShader = std::make_unique<Shader>("res/shaders/Texture.shader");
		m_OutlineShader = std::make_unique<Shader>("res/shaders/Outline.shader");

		std::map<GLenum, GLint> options =
		{
			{ GL_TEXTURE_MIN_FILTER, GL_LINEAR },
			{ GL_TEXTURE_MAG_FILTER, GL_LINEAR },
			{ GL_TEXTURE_WRAP_S, GL_REPEAT },
			{ GL_TEXTURE_WRAP_T, GL_REPEAT },
		};

		m_CubeTexture = std::make_unique<Texture>("res/textures/minecraft/grass_bottom.jpg");
		m_PlaneTexture = std::make_unique<Texture>("res/textures/minecraft/grass_top.jpg", GL_TEXTURE_2D, options);

		m_CubeVAO->Unbind();
		m_CubeVBO->Unbind();
		m_PlaneVAO->Unbind();
		m_PlaneVBO->Unbind();
	}

	TestStencil::~TestStencil()
	{
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_STENCIL_TEST);
		// Default values
		glStencilFunc(GL_EQUAL, 1, 0xFF);
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	}

	void TestStencil::OnUpdate(GLFWwindow* window, float deltaTime, Camera& camera)
	{
		camera.CameraInput(window, deltaTime);
		m_View = camera.GetLookAt();
		m_FoV = camera.GetZoom();
	}

	void TestStencil::OnRender()
	{
		Renderer renderer;

		glEnable(GL_STENCIL_TEST);
		glEnable(GL_DEPTH_TEST);
		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		// Specifies which action to take when updating stencil buffer;
		// 1) when stencil test fails,
		// 2) when stencil test passes but depth test fails, and
		// 3) when both stencil and depth test pass
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

		glm::mat4 projection = glm::perspective(glm::radians(m_FoV), 960.0f / 540.0f, 0.1f, 100.0f);

		// Render scene
		glStencilMask(0x00); // Ensure that the stencil buffer is not updated for the plane
		m_PlaneTexture->Bind(0);
		m_TextureShader->SetUniformMat4f("u_MVP", projection * m_View);
		renderer.Draw(*m_PlaneVAO, *m_TextureShader, 6);

		// First pass; draw objects as normal and write to stencil buffer
		glStencilFunc(GL_ALWAYS, 1, 0xFF); // Always pass fragment through stencil test
		glStencilMask(0xFF); // Enable writes

		m_TextureShader->Bind();
		m_TextureShader->SetUniform1i("u_Texture", 0);
		m_CubeTexture->Bind(0);

		glm::mat4 modelCube1 = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, -1.0f));
		m_TextureShader->SetUniformMat4f("u_MVP", projection * m_View * modelCube1);
		renderer.Draw(*m_CubeVAO, *m_TextureShader, 36);

		glm::mat4 modelCube2 = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f));
		m_TextureShader->SetUniformMat4f("u_MVP", projection * m_View * modelCube2);
		renderer.Draw(*m_CubeVAO, *m_TextureShader, 36);

		// Second pass; draw slightly scaled versions of cubes and disable stencil writing
		glStencilFunc(GL_NOTEQUAL, 1, 0xFF); // Pass fragment if value in stencil buffer is not equal to 1
		glStencilMask(0x00); // Disable writes
		glDisable(GL_DEPTH_TEST); // Disabling so that the scaled up cubes do not get overwritten by the plane

		float scale = 1.1f;
		m_OutlineShader->Bind();

		glm::mat4 modelCube1Outlined = glm::scale(modelCube1, glm::vec3(scale));
		m_OutlineShader->SetUniformMat4f("u_MVP", projection * m_View * modelCube1Outlined);
		renderer.Draw(*m_CubeVAO, *m_OutlineShader, 36);

		glm::mat4 modelCube2Outlined = glm::scale(modelCube2, glm::vec3(scale));
		m_OutlineShader->SetUniformMat4f("u_MVP", projection * m_View * modelCube2Outlined);
		renderer.Draw(*m_CubeVAO, *m_OutlineShader, 36);

		glStencilMask(0xFF);
		glStencilFunc(GL_ALWAYS, 0, 0xFF);
		glEnable(GL_DEPTH_TEST);
	}
}