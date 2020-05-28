#pragma once

//#include "VertexBuffer.h"
//#include "Buffer.h"

//class VertexBufferLayout;

namespace rxogl
{
	class VertexBuffer;
	class BufferLayout;
	class VertexArray
	{
	private:
		unsigned int m_RendererID;
	public:
		VertexArray();
		~VertexArray();

		void AddBuffer(const VertexBuffer& vb, const BufferLayout& layout);

		void Bind() const;
		void Unbind() const;
	};
}