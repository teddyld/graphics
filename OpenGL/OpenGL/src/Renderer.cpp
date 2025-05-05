#include <GL/glew.h>

#include <iostream>

#include "Renderer.h"

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		// OpenGL errors are defined in hexadecimal
		std::cout << "[OpenGL Error] (0x" << std::hex << error << "): " << function << " " << file << ":" << line << std::endl;
		return false;
	}
}

void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
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