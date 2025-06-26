#include "TestShadowMapping.h"

namespace test {
	TestShadowMapping::TestShadowMapping()
		: m_Selected(0), m_LightPos(-2.0f, 4.0f, -1.0f)
	{
		float cubeVertices[] = {
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
		};

		float planeVertices[] = {
			 20.0, -0.5f,  20.0, 0.0f, 1.0f, 0.0f, 20.0f, 0.0f,
			-20.0, -0.5f,  20.0, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
			-20.0, -0.5f, -20.0, 0.0f, 1.0f, 0.0f, 0.0f, 20.0f,

			 20.0, -0.5f,  20.0, 0.0f, 1.0f, 0.0f, 20.0f, 0.0f,
			-20.0, -0.5f, -20.0, 0.0f, 1.0f, 0.0f, 0.0f, 20.0f,
			 20.0, -0.5f, -20.0, 0.0f, 1.0f, 0.0f, 20.0f, 20.0f
		};

		float quadVertices[] = {
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
			 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
			-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
		};

		unsigned int indices[] = {
			0, 1, 2, 2, 3, 0
		};

		m_CubeVAO = std::make_unique<VertexArray>();
		m_CubeVBO = std::make_unique<VertexBuffer>(cubeVertices, 36 * 8 * sizeof(float), GL_STATIC_DRAW);

		VertexBufferLayout layout;
		layout.Push(GL_FLOAT, 3, GL_FALSE);
		layout.Push(GL_FLOAT, 3, GL_FALSE);
		layout.Push(GL_FLOAT, 2, GL_FALSE);
		m_CubeVAO->AddBuffer(*m_CubeVBO, layout);

		m_CubeVAO->Unbind();
		m_CubeVBO->Unbind();

		m_FloorVAO = std::make_unique<VertexArray>();
		m_FloorVBO = std::make_unique<VertexBuffer>(planeVertices, 6 * 8 * sizeof(float), GL_STATIC_DRAW);
		m_FloorVAO->AddBuffer(*m_FloorVBO, layout);

		m_FloorVAO->Unbind();
		m_FloorVBO->Unbind();

		m_QuadVAO = std::make_unique<VertexArray>();
		m_QuadEBO = std::make_unique<IndexBuffer>(indices, 6);
		m_QuadVBO = std::make_unique<VertexBuffer>(quadVertices, 4 * 5 * sizeof(float), GL_STATIC_DRAW);

		VertexBufferLayout quadLayout;
		quadLayout.Push(GL_FLOAT, 3, GL_FALSE);
		quadLayout.Push(GL_FLOAT, 2, GL_FALSE);
		m_QuadVAO->AddBuffer(*m_QuadVBO, quadLayout);

		m_QuadVAO->Unbind();
		m_QuadVBO->Unbind();
		m_QuadEBO->Unbind();

		m_DepthMapShader = std::make_unique<Shader>("res/shaders/shadow_mapping/DepthMap.shader");
		m_DebugQuadShader = std::make_unique<Shader>("res/shaders/shadow_mapping/DebugDepthMap.shader");
		m_ShadowShader = std::make_unique<Shader>("res/shaders/shadow_mapping/Shadow.shader");
		m_LightCubeShader = std::make_unique<Shader>("res/shaders/LightCube.shader");

		m_CubeTexture = std::make_unique<Texture>("res/textures/opengl/container2.png");
		std::map<GLenum, GLint> options = {
			{ GL_TEXTURE_MIN_FILTER, GL_LINEAR },
			{ GL_TEXTURE_MAG_FILTER, GL_LINEAR },
			{ GL_TEXTURE_WRAP_S, GL_REPEAT },
			{ GL_TEXTURE_WRAP_T, GL_REPEAT },
		};
		m_FloorTexture = std::make_unique<Texture>("res/textures/opengl/wood_floor.png", GL_TEXTURE_2D, options);
		m_LightTexture = std::make_unique<Texture>("res/textures/minecraft/glowstone.jpg");

		m_DepthMapFBO = std::make_unique<FrameBuffer>(1024, 1024, GL_TEXTURE_2D);
		m_DepthMapFBO->AttachDepthMap();
		m_DepthMapFBO->Unbind();
	}

	TestShadowMapping::~TestShadowMapping()
	{
		glDisable(GL_DEPTH_TEST);
	}

	void TestShadowMapping::OnUpdate(GLFWwindow* window, float deltaTime, Camera& camera)
	{
		camera.CameraInput(window, deltaTime);
		m_Transforms = camera.GetTransformMatrices();
		m_ViewPos = camera.GetPosition();
	}

	void TestShadowMapping::OnRender()
	{
		Renderer renderer;
		glEnable(GL_DEPTH_TEST);

		// lightProjection * lightView forms the light projection matrix T
		glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 7.5f);
		glm::mat4 lightView = glm::lookAt(glm::vec3(-2.0f, 4.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 lightSpaceMatrix = lightProjection * lightView;

		// Adjust viewport to shadow map resolution
		glViewport(0, 0, 1024, 1024);

		// Render scene from light's point of view into depth map fbo
		m_DepthMapFBO->Bind();
		renderer.Clear();

		m_DepthMapShader->Bind();
		m_DepthMapShader->SetUniformMat4f("u_LightSpaceMatrix", lightSpaceMatrix);

		// Fix peter panning by culling front faces during shadow map generation
		glCullFace(GL_FRONT);
		RenderScene(*m_DepthMapShader, false);
		glCullFace(GL_BACK);

		// Reset viewport
		glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
		m_DepthMapFBO->Unbind();
		renderer.Clear();

		if (m_Selected == 0)
			RenderDepthMap();
		else
		{
			m_ShadowShader->Bind();
			m_DepthMapFBO->BindTexture(1);
			m_ShadowShader->SetUniform1i("u_ShadowMap", 1);
			m_ShadowShader->SetUniformMat4f("u_LightSpaceMatrix", lightSpaceMatrix);

			m_ShadowShader->SetUniform1i("U_Material.diffuse", 0);
			m_ShadowShader->SetUniform1f("u_Material.shininess", 32.0f);

			m_ShadowShader->SetUniformMat4f("u_View", m_Transforms.view);
			m_ShadowShader->SetUniformMat4f("u_Projection", m_Transforms.projection);
			m_ShadowShader->SetUniform3f("u_ViewPos", m_ViewPos.x, m_ViewPos.y, m_ViewPos.z);

			m_ShadowShader->SetUniform3f("u_Light.position", m_LightPos.x, m_LightPos.y, m_LightPos.z);
			m_ShadowShader->SetUniform3f("u_Light.diffuse", 1.0f, 1.0f, 1.0f);
			m_ShadowShader->SetUniform3f("u_Light.ambient", 0.05f, 0.05f, 0.05f);
			m_ShadowShader->SetUniform3f("u_Light.specular", 0.3f, 0.3f, 0.3f);

			RenderScene(*m_ShadowShader, true);
		}
	}

	void TestShadowMapping::OnImGuiRender()
	{
		if (ImGui::RadioButton("Shadow map", m_Selected == 0))
			m_Selected = 0;
		if (ImGui::RadioButton("Disable shadows", m_Selected == 1))
			m_Selected = 1;
	}

	void TestShadowMapping::RenderScene(Shader& shader, bool textured)
	{
		Renderer renderer;

		shader.Bind();

		// Render cubes
		std::vector<glm::vec3> cubePositions = {
			glm::vec3(0.0f, 1.5f, 0.0f),
			glm::vec3(2.0f, 0.0f, 1.0f),
			glm::vec3(-1.0f, 0.0f, 2.0f)
		};

		if (textured)
			m_CubeTexture->Bind(0);

		for (int i = 0; i < 3; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			if (i == 2)
				model = glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0f, 0.0f, 1.0f)));

			model = glm::scale(model, glm::vec3(0.5f));
			shader.SetUniformMat4f("u_Model", model);

			renderer.Draw(*m_CubeVAO, shader, 36);
		}

		// Render floor
		if (textured)
			m_FloorTexture->Bind(0);

		shader.SetUniformMat4f("u_Model", glm::mat4(1.0f));

		renderer.Draw(*m_FloorVAO, shader, 6);

		// Render light
		if (textured)
		{
			m_LightTexture->Bind(0);
			m_LightCubeShader->Bind();
			m_LightCubeShader->SetUniform1i("u_Texture", 0);

			glm::mat4 lightModel = glm::translate(glm::mat4(1.0f), m_LightPos);

			m_LightCubeShader->SetUniformMat4f("u_MVP", m_Transforms.projection * m_Transforms.view * lightModel);
			renderer.Draw(*m_CubeVAO, *m_LightCubeShader, 36);
		}
	}

	void TestShadowMapping::RenderDepthMap()
	{
		Renderer renderer;

		m_DebugQuadShader->Bind();
		m_DepthMapFBO->BindTexture(0);

		m_DebugQuadShader->SetUniform1i("u_DepthMap", 0);
		m_DebugQuadShader->SetUniform1f("u_Near", 1.0f);
		m_DebugQuadShader->SetUniform1f("u_Far", 7.5f);

		renderer.Draw(*m_QuadVAO, *m_QuadEBO, *m_DebugQuadShader);
	}
}