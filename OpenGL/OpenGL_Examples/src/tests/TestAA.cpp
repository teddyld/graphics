#include "TestAA.h"

namespace test {
	TestAA::TestAA()
		: m_Samples(2)
	{
		float cubeVertices[] = {
			-0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,

			-0.5f, -0.5f,  0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,

			-0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,

			0.5f,  0.5f,  0.5f,
			0.5f,  0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f, -0.5f,  0.5f,
			0.5f,  0.5f,  0.5f,

			-0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f, -0.5f,

			-0.5f, 0.5f, -0.5f,
			 0.5f, 0.5f, -0.5f,
			 0.5f, 0.5f,  0.5f,
			 0.5f, 0.5f,  0.5f,
			-0.5f, 0.5f,  0.5f,
			-0.5f, 0.5f, -0.5f,
		};

		float quadVertices[] = {
			-1.0f,  1.0f,  0.0f, 1.0f,
			-1.0f, -1.0f,  0.0f, 0.0f,
			 1.0f, -1.0f,  1.0f, 0.0f,

			-1.0f,  1.0f,  0.0f, 1.0f,
			 1.0f, -1.0f,  1.0f, 0.0f,
			 1.0f,  1.0f,  1.0f, 1.0f
		};

		m_CubeVAO = std::make_unique<VertexArray>();
		m_CubeVBO = std::make_unique<VertexBuffer>(cubeVertices, 36 * 3 * sizeof(float), GL_STATIC_DRAW);

		VertexBufferLayout layout;
		layout.Push(GL_FLOAT, 3, GL_FALSE);
		m_CubeVAO->AddBuffer(*m_CubeVBO, layout);

		m_QuadVAO = std::make_unique<VertexArray>();
		m_QuadVBO = std::make_unique<VertexBuffer>(quadVertices, 6 * 4 * sizeof(float), GL_STATIC_DRAW);

		VertexBufferLayout screenLayout;
		screenLayout.Push(GL_FLOAT, 2, GL_FALSE);
		screenLayout.Push(GL_FLOAT, 2, GL_FALSE);
		m_QuadVAO->AddBuffer(*m_QuadVBO, screenLayout);

		m_CubeShader = std::make_unique<Shader>("res/shaders/antialiasing/AntiAliasing.shader");

		m_ScreenShader = std::make_unique<Shader>("res/shaders/antialiasing/AAPost.shader");
		m_ScreenShader->Bind();
		m_ScreenShader->SetUniform1i("u_ScreenTexture", 0);
		m_ScreenShader->Unbind();

		// Configure MSAA framebuffer
		m_FBO = std::make_unique<FrameBuffer>(SCR_WIDTH, SCR_HEIGHT, GL_TEXTURE_2D_MULTISAMPLE);
		m_FBO->AttachTextureMultisample(m_Samples);

		// Create multisampled renderbuffer object so all depth and stencil operations read from the currently bound framebuffer's depth and stencil attachments
		// Because the rbo is write-only (except using the slow glReadPixels) and the data is in native format (stored directly without conversions to texture-specific formats), rbo's are quite fast for writing data or copying data to other buffers
		// ... OpenGL can do memory optimisations that boost performance over textures for off-screen rendering to a framebuffer
		m_RBO = std::make_unique<RenderBuffer>(SCR_WIDTH, SCR_HEIGHT);
		m_RBO->ConfigureMultisampled(m_Samples);
		m_RBO->AttachBuffer();

		m_FBO->Unbind();
		m_RBO->Unbind();

		// Configure second post-processing framebuffer (only need color buffer, ignoring depth and stencil buffers)
		m_IntermediateFBO = std::make_unique<FrameBuffer>(SCR_WIDTH, SCR_HEIGHT, GL_TEXTURE_2D);
		m_IntermediateFBO->AttachTexture();

		m_IntermediateFBO->Unbind();

		m_CubeVAO->Unbind();
		m_CubeVBO->Unbind();
		m_QuadVAO->Unbind();
		m_QuadVBO->Unbind();
	}

	TestAA::~TestAA()
	{
		glDisable(GL_DEPTH_TEST);
	}

	void TestAA::OnUpdate(GLFWwindow* window, float deltaTime, Camera& camera)
	{
		camera.CameraInput(window, deltaTime);
		m_Transforms = camera.GetTransformMatrices();
	}

	void TestAA::OnRender()
	{
		Renderer renderer;

		glEnable(GL_MULTISAMPLE);
		glfwWindowHint(GLFW_SAMPLES, m_Samples); // Enable multisampling anti-aliasing (MSAAxN)

		m_FBO->Bind();
		renderer.Clear();
		glEnable(GL_DEPTH_TEST);

		m_CubeShader->Bind();
		m_CubeShader->SetUniformMat4f("u_Model", glm::mat4(1.0f));
		m_CubeShader->SetUniformMat4f("u_Projection", m_Transforms.projection);
		m_CubeShader->SetUniformMat4f("u_View", m_Transforms.view);

		renderer.Draw(*m_CubeVAO, *m_CubeShader, 36);

		// Blit multisampled buffer(s) to normal colorbuffer of intermediate FBO
		m_FBO->CopyToBuffer(*m_IntermediateFBO);

		// Render quad with scene's visuals
		m_FBO->Unbind();
		renderer.Clear();
		glDisable(GL_DEPTH_TEST);
		m_IntermediateFBO->BindTexture(0);

		renderer.Draw(*m_QuadVAO, *m_ScreenShader, 6);
	}

	void TestAA::OnImGuiRender()
	{
	}
}