#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexBufferLayout;

class VertexArray
{
private:
	unsigned int m_ID;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout, int index = 0);
	void AddBufferInstanced(const VertexBuffer& vb, const VertexBufferLayout& layout, int index = 0, int divisor = 1);

	void Bind() const;
	void Unbind() const;
};