#include "UniformBuffer.h"

UniformBuffer::UniformBuffer(GLsizeiptr size, unsigned int usage)
{
	glGenBuffers(1, &m_ID);
	Bind();
	glBufferData(GL_UNIFORM_BUFFER, size, nullptr, usage);
}

UniformBuffer::~UniformBuffer()
{
	glDeleteBuffers(1, &m_ID);
}

void UniformBuffer::BindBlock(const Shader& shader, const char* name, int bindingPoint)
{
	unsigned int uniformBlockIndex = glGetUniformBlockIndex(shader.GetID(), name); // Returns the uniform block index of a named uniform block inside the shader program
	glUniformBlockBinding(shader.GetID(), uniformBlockIndex, bindingPoint); // Set uniform block to specific binding point
}

void UniformBuffer::UpdateBufferSubData(int offset, GLsizeiptr size, const void* data)
{
	Bind();
	glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
	Unbind();
}

void UniformBuffer::BindBufferRange(int bindingPoint, int offset, GLsizeiptr size)
{
	glBindBufferRange(GL_UNIFORM_BUFFER, bindingPoint, m_ID, offset, size); // Bind range of buffer object to binding point
}

void UniformBuffer::Bind() const
{
	glBindBuffer(GL_UNIFORM_BUFFER, m_ID);
}

void UniformBuffer::Unbind() const
{
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}