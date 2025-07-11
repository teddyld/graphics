#include "Renderer.h"

GLenum glCheckError_(const char* file, int line)
{
	GLenum errorCode;
	while ((errorCode = glGetError()) != GL_NO_ERROR)
	{
		std::string error;
		switch (errorCode)
		{
		case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
		case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
		case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
		case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
		case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
		case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
		case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
		}
		std::cout << error << " | " << file << " (" << line << ")" << std::endl;
	}
	return errorCode;
}

void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	shader.Bind();
	va.Bind();

	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Draw(const VertexArray& va, const Shader& shader, int count) const
{
	shader.Bind();
	va.Bind();

	glDrawArrays(GL_TRIANGLES, 0, count);
}

void Renderer::DrawInstance(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, int instanceCount) const
{
	shader.Bind();
	va.Bind();

	glDrawElementsInstanced(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr, instanceCount);
}

void Renderer::DrawInstance(const VertexArray& va, const Shader& shader, int count, int instanceCount) const
{
	shader.Bind();
	va.Bind();

	glDrawArraysInstanced(GL_TRIANGLES, 0, count, instanceCount);
}

void Renderer::EnableColorBuffers(unsigned int number)
{
	if (number > GL_MAX_COLOR_ATTACHMENTS)
	{
		std::cout << "Maximum number of color attachments (" + std::to_string(GL_MAX_COLOR_ATTACHMENTS) + ") exceeded. Got " + std::to_string(number) << "\n";
		return;
	}

	std::vector<unsigned int> attachments;
	for (unsigned int i = 0; i < number; i++)
	{
		attachments.push_back(GL_COLOR_ATTACHMENT0 + i);
	}

	glDrawBuffers(number, attachments.data());
}