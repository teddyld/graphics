#pragma once
#include <memory>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Renderer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"

struct EntityVertex
{
	glm::vec3 position;
	glm::vec2 texCoords;
	float texIndex;
};

class Entity
{
protected:
	float m_Speed;
	glm::vec3 m_Position;
	glm::mat4 m_Model;

	std::unique_ptr<VertexArray> m_VAO;
	std::unique_ptr<VertexBuffer> m_VBO;
	std::unique_ptr<IndexBuffer> m_EBO;
	std::unique_ptr<Shader> m_Shader;
public:
	Entity(glm::mat4 model, float speed, glm::vec3 position)
		: m_Model(model), m_Speed(speed), m_Position(position) {}
	virtual ~Entity() {}

	virtual void OnUpdate(float deltaTime) {}
	virtual void OnRender(glm::mat4 view, glm::mat4 projection) {}
};