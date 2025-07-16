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

void FrameBuffer::AttachTexture1i(std::map<GLenum, GLint> options /*= fboDefaultOptions */)
{
	unsigned int texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	SetTextureParameters(GL_TEXTURE_2D, options);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

	glBindTexture(GL_TEXTURE_2D, 0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + (GLenum)m_Textures.size(), GL_TEXTURE_2D, texture, 0);
	m_Textures.push_back(texture);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete" << std::endl;
}

void FrameBuffer::AttachTexture1f(std::map<GLenum, GLint> options /*= fboDefaultOptions */)
{
	unsigned int texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	SetTextureParameters(GL_TEXTURE_2D, options);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_Width, m_Height, 0, GL_RGBA, GL_FLOAT, nullptr);

	glBindTexture(GL_TEXTURE_2D, 0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + (GLenum)m_Textures.size(), GL_TEXTURE_2D, texture, 0);
	m_Textures.push_back(texture);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete" << std::endl;
}

void FrameBuffer::AttachDepthMap()
{
	unsigned int depthMap;

	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);

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
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	m_Textures.push_back(depthMap);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete" << std::endl;
}

void FrameBuffer::AttachTextureMultisample(int samples, std::map<GLenum, GLint> options /*= fboDefaultOptions */)
{
	unsigned int texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, texture);

	SetTextureParameters(GL_TEXTURE_2D_MULTISAMPLE, options);
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_RGB, m_Width, m_Height, GL_TRUE);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + (GLenum)m_Textures.size(), GL_TEXTURE_2D_MULTISAMPLE, texture, 0);
	m_Textures.push_back(texture);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete" << std::endl;
}

void FrameBuffer::BindTexture(unsigned int slot /*= 0*/, unsigned int index /*= 0*/) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(m_Target, m_Textures[index]);
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