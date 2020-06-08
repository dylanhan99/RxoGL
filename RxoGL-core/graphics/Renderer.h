#pragma once

#include <gl/glew.h>
#include "Renderable2D.h"
#include "../ConstantsRxogl.h"

namespace rxogl
{
	//class IndexBuffer;
	class Renderer
	{
	public:
		virtual void Begin() {}
		virtual void Submit(const Renderable2D* renderable) = 0;
		virtual void End() {}
		virtual void Flush() = 0;
	//public:
	//	void Clear() const;
	//	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	};
}