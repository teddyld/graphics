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
	std::vector<unsigned int> m_Textures;
	int m_Width;
	int m_Height;
	GLenum m_Target;
public:
	inline static std::map<GLenum, GLint> fboDefaultOptions =
	{
		{ GL_TEXTURE_MIN_FILTER, GL_LINEAR },
		{ GL_TEXTURE_MAG_FILTER, GL_LINEAR },
		{ GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE },
		{ GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE },
	};

	FrameBuffer(int width, int height, GLenum target = GL_TEXTURE_2D);
	~FrameBuffer();

	// Declare a normalized fixed-point color buffer [0.0, 1.0] (8 bits per color component)
	void AttachTexture1i(std::map<GLenum, GLint> options = fboDefaultOptions);
	// Declare a floating point color buffer (16 bits per color component)
	void AttachTexture1f(std::map<GLenum, GLint> options = fboDefaultOptions);
	void AttachDepthMap();
	void AttachTextureMultisample(int samples, std::map<GLenum, GLint> options = fboDefaultOptions);
	void BindTexture(unsigned int slot = 0, unsigned int index = 0) const;
	void CopyToScreen(GLbitfield mask = GL_COLOR_BUFFER_BIT, GLenum filter = GL_NEAREST);
	void CopyToBuffer(const FrameBuffer& fbo, GLbitfield mask = GL_COLOR_BUFFER_BIT, GLenum filter = GL_NEAREST);

	void Bind() const;
	void Unbind() const;
};