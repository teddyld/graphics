#include "Texture.h"

unsigned int Texture::loadCubemap(std::vector<std::string> faces)
{
	return 0;
}

Texture::Texture(const std::string& path, GLenum target /*= GL_TEXTURE_2D */, std::map<GLenum, GLint> options /*= defaultOptions */)
	: m_ID(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0), m_Target(target)
{
	if (options.size() != 4)
	{
		std::cout << "Expected 4 options, got only " << options.size() << "\n";
	}

	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

	glGenTextures(1, &m_ID);
	glBindTexture(target, m_ID);

	if (target == GL_TEXTURE_2D)
	{
		for (const auto& [pname, param] : options)
		{
			glTexParameteri(target, pname, param);
		}

		glTexImage2D(target, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
		glBindTexture(target, 0);

		if (m_LocalBuffer)
		{
			stbi_image_free(m_LocalBuffer);
		}
		else
		{
			std::cout << "Failed to load texture: " << path << "\n";
		}
	}
	else if (target == GL_TEXTURE_CUBE_MAP)
	{
		// Not yet implemented
	}
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_ID);
}

void Texture::Bind(unsigned int slot /*= 0*/) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(m_Target, m_ID);
}

void Texture::Unbind() const
{
	glBindTexture(m_Target, 0);
}

void Texture::_Debug() const
{
	std::cout << "Path: " << m_FilePath << " Texture: " << m_ID << '\n';
}