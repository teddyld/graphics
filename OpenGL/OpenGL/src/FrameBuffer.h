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
	int m_Width;
	int m_Height;
	GLenum m_Target;
public:
	FrameBuffer(int width, int height, GLenum target = GL_TEXTURE_2D);
	~FrameBuffer();

	void AttachTexture(std::map<GLenum, GLint> options = defaultOptions);
	void AttachTexture(int samples, std::map<GLenum, GLint> options = defaultOptions);
	void BindTexture(unsigned int slot) const;
	void CopyToScreen(GLbitfield mask = GL_COLOR_BUFFER_BIT, GLenum filter = GL_NEAREST);
	void CopyToBuffer(const FrameBuffer& fbo, GLbitfield mask = GL_COLOR_BUFFER_BIT, GLenum filter = GL_NEAREST);

	void Bind() const;
	void Unbind() const;
};