#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, GLsizeiptr size, unsigned int usage)
{
	glGenBuffers(1, &m_ID);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_ID);
}

void VertexBuffer::UpdateBufferSubData(int offset, GLsizeiptr size, const void* data) const
{
	Bind();
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
	Unbind();
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}