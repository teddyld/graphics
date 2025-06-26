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
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

	glBindTexture(GL_TEXTURE_2D, 0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Texture, 0);
}

void FrameBuffer::AttachDepthMap()
{
	glGenTextures(1, &m_Texture);
	glBindTexture(GL_TEXTURE_2D, m_Texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	// Prevent oversampling
	float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_Width, m_Height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Attach depth texture as framebuffer's depth buffer and invalidate the required colour buffer
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_Texture, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
}

void FrameBuffer::AttachTextureMultisample(int samples, std::map<GLenum, GLint> options /*= fboDefaultOptions */)
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