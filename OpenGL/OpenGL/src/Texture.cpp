#include "Texture.h"

void SetTextureParameters(GLenum target, std::map<GLenum, GLint> options)
{
	std::vector<GLenum> validOptions;
	for (const auto& [pname, param] : Texture::defaultOptions)
	{
		validOptions.push_back(pname);
	}

	// Set provided parameters
	for (const auto& [pname, param] : options)
	{
		if (!Texture::defaultOptions.count(pname))
			std::cout << "Invalid option attribute \"" << pname << "\" \n";
		else
		{
			glTexParameteri(target, pname, param);
			auto it = std::find(validOptions.begin(), validOptions.end(), pname);
			if (it != validOptions.end())
				validOptions.erase(it);
		}
	}

	// Give remaining parameters default values
	for (const auto& pname : validOptions)
	{
		glTexParameteri(target, pname, Texture::defaultOptions.at(pname));
	}
}

TextureFormat GetTextureFormat(int nrComponents, bool gammaCorrection)
{
	GLenum internalFormat;
	GLenum dataFormat;

	if (nrComponents == 1)
	{
		internalFormat = GL_RED;
		dataFormat = GL_RED;
	}
	else
	{
		internalFormat = gammaCorrection ? GL_SRGB_ALPHA : GL_RGBA;
		dataFormat = GL_RGBA;
	}

	return {
		internalFormat, dataFormat
	};
}

Texture::Texture(const std::string& path, GLenum target /*= GL_TEXTURE_2D */, std::map<GLenum, GLint> options /*= defaultOptions */, bool gammaCorrection /*= false */)
	: m_ID(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0), m_Target(target)
{
	glGenTextures(1, &m_ID);
	glBindTexture(target, m_ID);

	SetTextureParameters(target, options);

	if (target == GL_TEXTURE_2D)
	{
		stbi_set_flip_vertically_on_load(1);
		m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);
		TextureFormat format = GetTextureFormat(m_BPP, gammaCorrection);

		glTexImage2D(target, 0, format.internalFormat, m_Width, m_Height, 0, format.dataFormat, GL_UNSIGNED_BYTE, m_LocalBuffer);
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
		std::vector<std::string> faces =
		{
			"right.jpg",
			"left.jpg",
			"top.jpg",
			"bottom.jpg",
			"front.jpg",
			"back.jpg"
		};

		for (unsigned int i = 0; i < faces.size(); i++)
		{
			m_LocalBuffer = stbi_load((path + "/" + faces[i]).c_str(), &m_Width, &m_Height, &m_BPP, 4);
			TextureFormat format = GetTextureFormat(m_BPP, gammaCorrection);

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format.internalFormat, m_Width, m_Height, 0, format.dataFormat, GL_UNSIGNED_BYTE, m_LocalBuffer);

			if (m_LocalBuffer)
			{
				stbi_image_free(m_LocalBuffer);
			}
			else
			{
				std::cout << "Failed to load texture: " << path << "\n";
			}
		}
	}
}

Texture::Texture(const void* data, int width, int height)
	: m_ID(0), m_FilePath(""), m_LocalBuffer(nullptr), m_Width(width), m_Height(height), m_BPP(0), m_Target(GL_TEXTURE_2D)
{
	glGenTextures(1, &m_ID);
	glBindTexture(GL_TEXTURE_2D, m_ID);

	std::map<GLenum, GLint> options =
	{
		{ GL_TEXTURE_MIN_FILTER, GL_NEAREST },
		{ GL_TEXTURE_MAG_FILTER, GL_NEAREST },
		{ GL_TEXTURE_WRAP_S, GL_REPEAT },
		{ GL_TEXTURE_WRAP_T, GL_REPEAT },
		{ GL_TEXTURE_WRAP_R, GL_REPEAT }
	};

	SetTextureParameters(GL_TEXTURE_2D, options);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, m_Width, m_Height, 0, GL_RGB, GL_FLOAT, data);
	glBindTexture(GL_TEXTURE_2D, 0);
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