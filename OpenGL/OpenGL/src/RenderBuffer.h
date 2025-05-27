#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

class RenderBuffer
{
private:
	unsigned int m_ID;
public:
	RenderBuffer(float width, float height);
	~RenderBuffer();

	void AttachBuffer();

	void Bind() const;
	void Unbind() const;
};