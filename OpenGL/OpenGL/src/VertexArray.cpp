#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_ID);
	Bind();
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_ID);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout, int index /*= 0*/)
{
	vb.Bind();

	uintptr_t offset = 0;

	const auto& elements = layout.GetElements();
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		glEnableVertexAttribArray(i + index);
		glVertexAttribPointer(i + index, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void VertexArray::AddBufferInstanced(const VertexBuffer& vb, const VertexBufferLayout& layout, int index /*= 0*/, int divisor /*= 1*/)
{
	vb.Bind();

	uintptr_t offset = 0;

	const auto& elements = layout.GetElements();
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		glEnableVertexAttribArray(i + index);
		glVertexAttribPointer(i + index, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);
		glVertexAttribDivisor(i + index, divisor);
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_ID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}