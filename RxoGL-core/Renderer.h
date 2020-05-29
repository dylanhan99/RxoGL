#pragma once

#include <gl/glew.h>
#include "VertexArray.h"
#include "graphics/Shader.h"
#include "ConstantsRxogl.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line); 

namespace rxogl
{
	class IndexBuffer;
	class Renderer
	{
	private:
		constants::Vertex* QuadBuffer; // CPU side storage for vertex buffer
		constants::Vertex* QuadBufferPtr; // 
	public:
		void Clear() const;
		void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	};
}