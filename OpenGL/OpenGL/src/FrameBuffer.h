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

	void AttachTexture(float width, float height);
	void AttachTexture(float width, float height, std::map<GLenum, GLint> options);
	void BindTexture(unsigned int slot) const;
	void AttachRenderbuffer(const RenderBuffer& rbo);

	void Bind() const;
	void Unbind() const;
};