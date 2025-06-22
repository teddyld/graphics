#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(int width, int height, GLenum target /*= GL_TEXTURE_2D */)
	: m_Width(width), m_Height(height), m_Target(target)
{
	glGenFramebuffers(1, &m_ID);
	Bind();
}

FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &m_ID);
}

void FrameBuffer::AttachTexture(std::map<GLenum, GLint> options /*= fboDefaultOptions */)
{
	glGenTextures(1, &m_Texture);
	glBindTexture(GL_TEXTURE_2D, m_Texture);

	SetTextureParameters(GL_TEXTURE_2D, options);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Texture, 0);
}

void FrameBuffer::AttachTexture(int samples, std::map<GLenum, GLint> options /*= fboDefaultOptions */)
{
	glGenTextures(1, &m_Texture);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_Texture);

	SetTextureParameters(GL_TEXTURE_2D_MULTISAMPLE, options);
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_RGB, m_Width, m_Height, GL_TRUE);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, m_Texture, 0);
}

void FrameBuffer::BindTexture(unsigned int slot /*= 0*/) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(m_Target, m_Texture);
}

void FrameBuffer::CopyToScreen(GLbitfield mask /*= GL_COLOR_BUFFER_BIT*/, GLenum filter /*= GL_NEAREST */)
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, m_ID);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glBlitFramebuffer(0, 0, m_Width, m_Height, 0, 0, m_Width, m_Height, mask, filter);
}

void FrameBuffer::CopyToBuffer(const FrameBuffer& fbo, GLbitfield mask /*= GL_COLOR_BUFFER_BIT*/, GLenum filter /*= GL_NEAREST */)
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, m_ID);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo.m_ID);
	glBlitFramebuffer(0, 0, m_Width, m_Height, 0, 0, m_Width, m_Height, mask, filter);
}

void FrameBuffer::Bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
}

void FrameBuffer::Unbind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}