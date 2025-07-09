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
	inline static std::map<GLenum, GLint> fboDefaultOptions =
	{
		{ GL_TEXTURE_MIN_FILTER, GL_LINEAR },
		{ GL_TEXTURE_MAG_FILTER, GL_LINEAR },
	};

	FrameBuffer(int width, int height, GLenum target = GL_TEXTURE_2D);
	~FrameBuffer();

	void AttachTexture(std::map<GLenum, GLint> options = fboDefaultOptions);
	void AttachTexturef(std::map<GLenum, GLint> options = fboDefaultOptions);
	void AttachDepthMap();
	void AttachTextureMultisample(int samples, std::map<GLenum, GLint> options = fboDefaultOptions);
	void BindTexture(unsigned int slot) const;
	void CopyToScreen(GLbitfield mask = GL_COLOR_BUFFER_BIT, GLenum filter = GL_NEAREST);
	void CopyToBuffer(const FrameBuffer& fbo, GLbitfield mask = GL_COLOR_BUFFER_BIT, GLenum filter = GL_NEAREST);

	void Bind() const;
	void Unbind() const;
};