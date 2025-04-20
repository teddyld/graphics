#include "Renderer.h"

#include <iostream>

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		// OpenGL errors are defined in hexadecimal
		std::cout << "[OpenGL Error] (0x" << std::hex << error << "): " << function << " " << file << ":" << line << std::endl;
		return false;
	}
}