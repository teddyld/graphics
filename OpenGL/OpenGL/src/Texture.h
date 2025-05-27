#pragma once

#include <GL/glew.h>

#include <map>
#include <iostream>

#include "stb_image/stb_image.h"

class Texture
{
private:
	unsigned int m_ID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
public:
	Texture(const std::string& path);
	Texture(const std::string& path, std::map<GLenum, GLint> options);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;
	void _Debug() const;

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
	inline int GetID() const { return m_ID; }
};