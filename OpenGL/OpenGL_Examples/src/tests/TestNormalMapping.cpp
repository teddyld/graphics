#include "TestNormalMapping.h"

namespace test {
	TestNormalMapping::TestNormalMapping()
	{
		float cubeVertices[] = {
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f, 0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f, 1.0f, 0.0f,
			-0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
			-0.5f, -0.5f,  0.5f, 0.0f, 1.0f,
			-0.5f,  0.5f,  0.5f, 0.0f, 0.0f,

			 0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
			 0.5f,  0.5f, -0.5f, 1.0f, 0.0f,
			 0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f, 0.0f, 1.0f,
			 0.5f,  0.5f,  0.5f, 0.0f, 0.0f,

			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f, 1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f, 1.0f, 1.0f,
			-0.5f, -0.5f,  0.5f, 0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

			-0.5f,  0.5f, -0.5f, 0.0f, 0.0f,
			 0.5f,  0.5f, -0.5f, 1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f, 0.0f, 1.0f,
			-0.5f,  0.5f, -0.5f, 0.0f, 0.0f,
		};

		m_LightVAO = std::make_unique<VertexArray>();
		m_LightVBO = std::make_unique<VertexBuffer>(cubeVertices, 36 * 5 * sizeof(float), GL_STATIC_DRAW);

		VertexBufferLayout lightLayout;
		lightLayout.Push(GL_FLOAT, 3, GL_FALSE);
		lightLayout.Push(GL_FLOAT, 2, GL_FALSE);
		m_LightVAO->AddBuffer(*m_LightVBO, lightLayout);

		m_LightDiffuse = std::make_unique<Texture>("res/textures/minecraft/glowstone.jpg");
		m_LightShader = std::make_unique<Shader>("res/shaders/Texture.shader");
		m_LightShader->Bind();
		m_LightShader->SetUniform1i("u_Texture", 0);
		m_LightShader->Unbind();

		// positions
		glm::vec3 pos1(-1.0f, 1.0f, 0.0f);
		glm::vec3 pos2(-1.0f, -1.0f, 0.0f);
		glm::vec3 pos3(1.0f, -1.0f, 0.0f);
		glm::vec3 pos4(1.0f, 1.0f, 0.0f);
		// texture coordinates
		glm::vec2 uv1(0.0f, 1.0f);
		glm::vec2 uv2(0.0f, 0.0f);
		glm::vec2 uv3(1.0f, 0.0f);
		glm::vec2 uv4(1.0f, 1.0f);
		// normal vector
		glm::vec3 nm(0.0f, 0.0f, 1.0f);

		// calculate tangent/bitangent vectors of both triangles
		glm::vec3 tangent1, bitangent1;
		glm::vec3 tangent2, bitangent2;
		// triangle 1
		// ----------
		glm::vec3 edge1 = pos2 - pos1;
		glm::vec3 edge2 = pos3 - pos1;
		glm::vec2 deltaUV1 = uv2 - uv1;
		glm::vec2 deltaUV2 = uv3 - uv1;

		float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

		tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
		tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
		tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

		bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
		bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
		bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);

		// triangle 2
		// ----------
		edge1 = pos3 - pos1;
		edge2 = pos4 - pos1;
		deltaUV1 = uv3 - uv1;
		deltaUV2 = uv4 - uv1;

		f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

		tangent2.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
		tangent2.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
		tangent2.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

		bitangent2.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
		bitangent2.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
		bitangent2.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);

		float vertices[] = {
			// positions            // normal         // texcoords  // tangent                          // bitangent
		   pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
		   pos2.x, pos2.y, pos2.z, nm.x, nm.y, nm.z, uv2.x, uv2.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
		   pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,

		   pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
		   pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
		   pos4.x, pos4.y, pos4.z, nm.x, nm.y, nm.z, uv4.x, uv4.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z
		};

		m_PlaneVAO = std::make_unique<VertexArray>();
		m_PlaneVBO = std::make_unique<VertexBuffer>(vertices, 6 * 14 * sizeof(float), GL_STATIC_DRAW);

		VertexBufferLayout planelayout;
		planelayout.Push(GL_FLOAT, 3, GL_FALSE);
		planelayout.Push(GL_FLOAT, 3, GL_FALSE);
		planelayout.Push(GL_FLOAT, 2, GL_FALSE);
		planelayout.Push(GL_FLOAT, 3, GL_FALSE);
		planelayout.Push(GL_FLOAT, 3, GL_FALSE);
		m_PlaneVAO->AddBuffer(*m_PlaneVBO, planelayout);

		m_PlaneDiffuse = std::make_unique<Texture>("res/textures/opengl/brickwall.jpg");
		m_PlaneNormalMap = std::make_unique<Texture>("res/textures/opengl/brickwall_normal.jpg");
		m_PlaneShader = std::make_unique<Shader>("res/shaders/normal_mapping/Normal.shader");
		m_PlaneShader->Bind();

		m_PlaneShader->SetUniform3f("u_Light.diffuse", 1.0f, 1.0f, 1.0f);
		m_PlaneShader->SetUniform3f("u_Light.ambient", 0.05f, 0.05f, 0.05f);
		m_PlaneShader->SetUniform3f("u_Light.specular", 0.3f, 0.3f, 0.3f);
		m_PlaneShader->SetUniform1i("u_Material.diffuse", 0);
		m_PlaneShader->SetUniform1i("u_Material.normal", 1);
		m_PlaneShader->SetUniform1f("u_Material.shininess", 0.5f);

		m_PlaneShader->Unbind();

		m_LightVAO->Unbind();
		m_LightVBO->Unbind();
		m_PlaneVAO->Unbind();
		m_PlaneVBO->Unbind();
	}

	TestNormalMapping::~TestNormalMapping()
	{
		glDisable(GL_DEPTH_TEST);
	}

	void TestNormalMapping::OnUpdate(GLFWwindow* window, float deltaTime, Camera& camera)
	{
		camera.CameraInput(window, deltaTime);
		m_Transforms = camera.GetTransformMatrices();
		m_ViewPos = camera.GetPosition();
	}

	void TestNormalMapping::OnRender()
	{
		Renderer renderer;

		glEnable(GL_DEPTH_TEST);

		glm::vec3 lightPosition(2.0 * sin(glfwGetTime()), 0.0f, 2.0f);

		m_PlaneShader->Bind();
		m_PlaneDiffuse->Bind(0);
		m_PlaneNormalMap->Bind(1);

		m_PlaneShader->SetUniform3f("u_LightPos", lightPosition.x, lightPosition.y, lightPosition.z);

		glm::mat4 planeModel = glm::rotate(glm::mat4(1.0f), glm::radians((float)glfwGetTime() * -10.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));

		m_PlaneShader->SetUniformMat4f("u_Model", planeModel);
		m_PlaneShader->SetUniformMat4f("u_Projection", m_Transforms.projection);
		m_PlaneShader->SetUniformMat4f("u_View", m_Transforms.view);
		m_PlaneShader->SetUniform3f("u_ViewPos", m_ViewPos.x, m_ViewPos.y, m_ViewPos.z);

		renderer.Draw(*m_PlaneVAO, *m_PlaneShader, 6);

		m_LightDiffuse->Bind(0);
		m_LightShader->Bind();

		glm::mat4 lightModel = glm::scale(glm::translate(glm::mat4(1.0f), lightPosition), glm::vec3(0.2f));

		m_LightShader->SetUniformMat4f("u_MVP", m_Transforms.projection * m_Transforms.view * lightModel);

		renderer.Draw(*m_LightVAO, *m_LightShader, 36);
	}
}