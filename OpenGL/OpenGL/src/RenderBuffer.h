#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

class RenderBuffer
{
private:
	unsigned int m_ID;
	int m_Width;
	int m_Height;
public:
	RenderBuffer(int width, int height);
	~RenderBuffer();

	void Configure();
	void ConfigureMultisampled(int samples);
	void AttachBuffer();

	void Bind() const;
	void Unbind() const;
};