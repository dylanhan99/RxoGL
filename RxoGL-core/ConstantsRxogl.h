#pragma once
#include <iostream>
#include <gl/glew.h>
#include <glm/glm.hpp>;

#include "vendor/FreeType/FreeType-gl.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << "): "
			<< function << " " << line << std::endl;
		return false;
	}
	return true;
}

static bool FTCall(FT_Error error)
{
	while (error != 0)
	{
		std::cout << "[FreeType Error] (" /*<< FT_Error_String(error)*/ << "): "
			<< __FILE__ << " " << __LINE__ << std::endl;
		return false;
	}
	return true;
}

namespace rxogl {
namespace constants {
	typedef glm::vec4 rxoPosition;
	typedef glm::vec4 rxoColor;
	typedef glm::vec2 rxoTexCoords;

	struct Vertex
	{
		rxoPosition		Position; // Vec4 because Homogeneous coordinates. The fourth element = 1
		rxoColor		Color;
		rxoTexCoords	TexCoords;
		float			TexIndex;
	};
}
}