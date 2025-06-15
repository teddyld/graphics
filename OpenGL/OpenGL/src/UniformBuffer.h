#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

class UniformBuffer
{
private:
	unsigned int m_ID;
public:
	UniformBuffer(GLsizeiptr size, unsigned int usage);
	~UniformBuffer();

	void BindBlock(const Shader& shader, const char* name, int bindingPoint);
	void BindBufferRange(int bindingPoint, int offset, GLsizeiptr size);
	void UpdateBufferSubData(int offset, GLsizeiptr size, const void* data);

	void Bind() const;
	void Unbind() const;
};