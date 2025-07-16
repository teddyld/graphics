#include "RenderBuffer.h"

RenderBuffer::RenderBuffer(int width, int height)
	: m_Width(width), m_Height(height)
{
	glGenRenderbuffers(1, &m_ID);
	Bind();
}

RenderBuffer::~RenderBuffer()
{
	glDeleteRenderbuffers(1, &m_ID);
}

void RenderBuffer::Configure()
{
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Width, m_Height);
}

void RenderBuffer::ConfigureMultisampled(int samples)
{
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, GL_DEPTH24_STENCIL8, m_Width, m_Height);
}

void RenderBuffer::AttachBuffer()
{
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_ID);
}

void RenderBuffer::Bind() const
{
	glBindRenderbuffer(GL_RENDERBUFFER, m_ID);
}

void RenderBuffer::Unbind() const
{
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}