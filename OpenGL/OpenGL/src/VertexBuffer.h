#pragma once

class VertexBuffer
{
private:
	unsigned int m_VBO;
public:
	VertexBuffer(const void* data, unsigned int size, unsigned int usage);
	~VertexBuffer();

	void UpdateBufferSubData(int offset, int size, const void* data) const;
	void Bind() const;
	void Unbind() const;
};