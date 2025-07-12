#pragma once

#include <GL/glew.h>

#include <iostream>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define glCheckError() glCheckError_(__FILE__, __LINE__)

GLenum glCheckError_(const char* file, int line);

class Renderer
{
private:
public:
	void Clear() const;
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	void Draw(const VertexArray& va, const Shader& shader, int count) const;
	void DrawInstance(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, int instanceCount) const;
	void DrawInstance(const VertexArray& va, const Shader& shader, int count, int instanceCount) const;

	void EnableColorBuffers(unsigned int number);
};