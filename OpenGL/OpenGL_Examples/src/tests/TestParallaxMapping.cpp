#include "TestParallaxMapping.h"

namespace test {
	TestParallaxMapping::TestParallaxMapping()
		: m_Selected(0), m_MinLayers(8), m_MaxLayers(32)
	{
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

		m_VAO = std::make_unique<VertexArray>();
		m_VBO = std::make_unique<VertexBuffer>(vertices, 6 * 14 * sizeof(float), GL_STATIC_DRAW);

		VertexBufferLayout layout;
		layout.Push(GL_FLOAT, 3, GL_FALSE);
		layout.Push(GL_FLOAT, 3, GL_FALSE);
		layout.Push(GL_FLOAT, 2, GL_FALSE);
		layout.Push(GL_FLOAT, 3, GL_FALSE);
		layout.Push(GL_FLOAT, 3, GL_FALSE);
		m_VAO->AddBuffer(*m_VBO, layout);

		m_Diffuse = std::make_unique<Texture>("res/textures/opengl/bricks2/bricks2.jpg");
		m_NormalMap = std::make_unique<Texture>("res/textures/opengl/bricks2/bricks2_normal.jpg");
		m_ParallaxMap = std::make_unique<Texture>("res/textures/opengl/bricks2/bricks2_disp.jpg");

		m_VAO->Unbind();
		m_VBO->Unbind();
	}

	TestParallaxMapping::~TestParallaxMapping()
	{
		glDisable(GL_DEPTH_TEST);
	}

	void TestParallaxMapping::OnUpdate(GLFWwindow* window, float deltaTime, Camera& camera)
	{
		camera.CameraInput(window, deltaTime);
		m_Transforms = camera.GetTransformMatrices();
		m_ViewPos = camera.GetPosition();
	}

	void TestParallaxMapping::OnRender()
	{
		Renderer renderer;

		glEnable(GL_DEPTH_TEST);

		glm::vec3 lightPosition(2.0 * sin(glfwGetTime()), 0.0f, 2.0f);

		if (m_Selected == 0)
			m_Shader = std::make_unique<Shader>("res/shaders/parallax_mapping/Parallax.shader");
		else if (m_Selected == 1)
			m_Shader = std::make_unique<Shader>("res/shaders/parallax_mapping/SteepParallax.shader");
		else
			m_Shader = std::make_unique<Shader>("res/shaders/parallax_mapping/ParallaxOcclusion.shader");

		m_Diffuse->Bind(0);
		m_NormalMap->Bind(1);
		m_ParallaxMap->Bind(2);

		m_Shader->Bind();

		m_Shader->SetUniform1i("u_MinLayers", m_MinLayers);
		m_Shader->SetUniform1i("u_MaxLayers", m_MaxLayers);

		m_Shader->SetUniform3f("u_Light.diffuse", 1.0f, 1.0f, 1.0f);
		m_Shader->SetUniform3f("u_Light.ambient", 0.05f, 0.05f, 0.05f);
		m_Shader->SetUniform3f("u_Light.specular", 0.3f, 0.3f, 0.3f);
		m_Shader->SetUniform1i("u_Material.diffuse", 0);
		m_Shader->SetUniform1i("u_Material.normal", 1);
		m_Shader->SetUniform1i("u_Material.depth", 2);
		m_Shader->SetUniform1f("u_Material.shininess", 0.5f);
		m_Shader->SetUniform1f("u_HeightScale", 0.1f);

		m_Shader->SetUniformMat4f("u_Model", glm::mat4(1.0f));
		m_Shader->SetUniformMat4f("u_Projection", m_Transforms.projection);
		m_Shader->SetUniformMat4f("u_View", m_Transforms.view);
		m_Shader->SetUniform3f("u_ViewPos", m_ViewPos.x, m_ViewPos.y, m_ViewPos.z);
		m_Shader->SetUniform3f("u_LightPos", lightPosition.x, lightPosition.y, lightPosition.z);

		renderer.Draw(*m_VAO, *m_Shader, 6);
	}

	void TestParallaxMapping::OnImGuiRender()
	{
		if (ImGui::RadioButton("Parallax mapping", m_Selected == 0))
			m_Selected = 0;
		if (ImGui::RadioButton("Steep parallax mapping", m_Selected == 1))
			m_Selected = 1;
		if (ImGui::RadioButton("Parallax occlusion mapping", m_Selected == 2))
			m_Selected = 2;

		if (m_Selected != 0)
		{
			ImGui::SliderInt("Min Depth Layers", &m_MinLayers, 0, m_MaxLayers);
			ImGui::SliderInt("Max Depth Layers", &m_MaxLayers, m_MinLayers, 100);
		}
	}
}