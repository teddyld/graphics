#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <map>

#include "Texture.h"
#include "RenderBuffer.h"

class FrameBuffer
{
private:
	unsigned int m_ID;
	unsigned int m_Texture;
public:
	FrameBuffer();
	~FrameBuffer();

	void AttachTexture(int width, int height);
	void AttachTexture(int width, int height, std::map<GLenum, GLint> options);
	void BindTexture(unsigned int slot) const;

	void Bind() const;
	void Unbind() const;
};