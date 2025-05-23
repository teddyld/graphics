#include <GL/glew.h>
#include <iostream>

#include "Texture.h"
#include "stb_image/stb_image.h"

Texture::Texture(const std::string& path)
	: m_Texture(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

	glGenTextures(1, &m_Texture);
	glBindTexture(GL_TEXTURE_2D, m_Texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (m_LocalBuffer)
	{
		stbi_image_free(m_LocalBuffer);
	}
	else
	{
		std::cout << "Failed to load texture: " << path << "\n";
	}
}

Texture::Texture(const std::string& path, std::map<GLenum, GLint> options)
	: m_Texture(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
{
	if (options.size() != 4)
	{
		std::cout << "Expected 4 options, got only " << options.size() << "\n";
	}

	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

	glGenTextures(1, &m_Texture);
	glBindTexture(GL_TEXTURE_2D, m_Texture);

	for (const auto& [pname, param] : options)
	{
		glTexParameteri(GL_TEXTURE_2D, pname, param);
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (m_LocalBuffer)
	{
		stbi_image_free(m_LocalBuffer);
	}
	else
	{
		std::cout << "Failed to load texture: " << path << std::endl;
	}
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_Texture);
}

void Texture::Bind(unsigned int slot /*= 0*/) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_Texture);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::_Debug() const
{
	std::cout << "Path: " << m_FilePath << " Texture: " << m_Texture << '\n';
}