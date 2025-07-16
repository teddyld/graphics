#pragma once

#include <GL/glew.h>

#include <map>
#include <iostream>
#include <vector>

#include "stb_image/stb_image.h"

struct TextureFormat
{
	GLenum internalFormat;
	GLenum dataFormat;
};

void SetTextureParameters(GLenum target, std::map<GLenum, GLint> options);
TextureFormat GetTextureFormat(int nrComponents, bool gammaCorrection);

class Texture
{
private:
	unsigned int m_ID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
	GLenum m_Target;
public:
	inline static std::map<GLenum, GLint> defaultOptions =
	{
		{ GL_TEXTURE_MIN_FILTER, GL_LINEAR },
		{ GL_TEXTURE_MAG_FILTER, GL_LINEAR },
		{ GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER },
		{ GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER },
		{ GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER }
	};

	Texture(const std::string& path, GLenum target = GL_TEXTURE_2D, std::map<GLenum, GLint> options = defaultOptions, bool gammaCorrected = false);
	Texture(const void* data, int width, int height);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	void _Debug() const;

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
	inline int GetID() const { return m_ID; }
};