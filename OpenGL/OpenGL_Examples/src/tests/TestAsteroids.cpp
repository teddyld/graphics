#include "TestAsteroids.h"

namespace test {
	TestAsteroids::TestAsteroids()
		: m_Amount(1000)
	{
		glm::mat4* modelMatrices;
		modelMatrices = new glm::mat4[m_Amount];
		srand((int)glfwGetTime()); // initialize random seed
		float radius = 50.0;
		float offset = 2.5f;
		for (unsigned int i = 0; i < m_Amount; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			// 1. translation: displace along circle with 'radius' in range [-offset, offset]
			float angle = (float)i / (float)m_Amount * 360.0f;
			float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
			float x = sin(angle) * radius + displacement;
			displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
			float y = displacement * 0.4f; // keep height of field smaller compared to width of x and z
			displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
			float z = cos(angle) * radius + displacement;
			model = glm::translate(model, glm::vec3(x, y, z));

			// 2. scale: scale between 0.05 and 0.25f
			float scale = (float)(rand() % 20) / 100.0f + 0.05f;
			model = glm::scale(model, glm::vec3(scale));

			// 3. rotation: add random rotation around a (semi)randomly picked rotation axis vector
			float rotAngle = (float)(rand() % 360);
			model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

			// 4. now add to list of matrices
			modelMatrices[i] = model;
		}

		m_RockObj = std::make_unique<Model>("res/objects/rock/rock.obj");
		m_PlanetObj = std::make_unique<Model>("res/objects/planet/planet.obj");
		m_InstanceShader = std::make_unique<Shader>("res/shaders/instancing/InstanceModel.shader");
		m_PlanetShader = std::make_unique<Shader>("res/shaders/Model.shader");

		m_VBO = std::make_unique<VertexBuffer>(&modelMatrices[0], m_Amount * sizeof(glm::mat4), GL_STATIC_DRAW);

		VertexBufferLayout layout;
		layout.Push(GL_FLOAT, 4, GL_FALSE);
		layout.Push(GL_FLOAT, 4, GL_FALSE);
		layout.Push(GL_FLOAT, 4, GL_FALSE);
		layout.Push(GL_FLOAT, 4, GL_FALSE);

		for (unsigned int i = 0; i < m_RockObj->m_Meshes.size(); i++)
		{
			std::shared_ptr<VertexArray> VAO = m_RockObj->m_Meshes[i].GetMeshVAO();
			VAO->Bind();
			VAO->AddBufferInstanced(*m_VBO, layout, 3, 1);
			VAO->Unbind();
		}
	}

	TestAsteroids::~TestAsteroids()
	{
		glDisable(GL_DEPTH_TEST);
	}

	void TestAsteroids::OnUpdate(GLFWwindow* window, float deltaTime, Camera& camera)
	{
		camera.CameraInput(window, deltaTime);
		m_Transforms = camera.GetTransformMatrices();
	}

	void TestAsteroids::OnRender()
	{
		Renderer renderer;
		glEnable(GL_DEPTH_TEST);
		glm::mat4 projection = m_Transforms.projection;
		glm::mat4 view = m_Transforms.view;

		m_InstanceShader->Bind();
		m_InstanceShader->SetUniformMat4f("u_Projection", projection);
		m_InstanceShader->SetUniformMat4f("u_View", view);

		for (unsigned int i = 0; i < m_RockObj->m_Meshes.size(); i++)
		{
			std::shared_ptr<VertexArray> VAO = m_RockObj->m_Meshes[i].GetMeshVAO();
			std::shared_ptr<IndexBuffer> EBO = m_RockObj->m_Meshes[i].GetMeshEBO();
			renderer.DrawInstance(*VAO, *EBO, *m_InstanceShader, m_Amount);
			VAO->Unbind();
		}

		m_PlanetShader->Bind();
		m_PlanetShader->SetUniformMat4f("u_Model", glm::mat4(1.0f));
		m_PlanetShader->SetUniformMat4f("u_Projection", projection);
		m_PlanetShader->SetUniformMat4f("u_View", view);

		m_PlanetObj->Draw(*m_PlanetShader);
	}
}