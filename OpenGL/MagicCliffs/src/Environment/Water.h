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

class Water
{
private:
	std::unique_ptr<VertexArray> m_VAO;
	std::unique_ptr<VertexBuffer> m_VBO;
	std::unique_ptr<IndexBuffer> m_EBO;
	std::unique_ptr<Shader> m_Shader;
	std::unique_ptr<Texture> m_Texture;
public:
	Water();

	void OnRender(glm::mat4 view, glm::mat4 projection);
};