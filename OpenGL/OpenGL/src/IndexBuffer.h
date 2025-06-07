#pragma once

#include <GL/glew.h>

class IndexBuffer
{
private:
	unsigned int m_ID;
	GLsizeiptr m_Count;
public:
	IndexBuffer(const unsigned int* data, GLsizeiptr count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline GLsizei GetCount() const { return (GLsizei)m_Count; }
};