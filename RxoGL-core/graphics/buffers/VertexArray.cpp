#include "VertexArray.h"

#include "Buffer.h"
#include "../Renderer2D.h"

namespace rxogl
{
	VertexArray::VertexArray()
	{
		GLCall(glGenVertexArrays(1, &m_RendererID));
		Bind();
	}

	VertexArray::~VertexArray()
	{
		GLCall(glDeleteVertexArrays(1, &m_RendererID));
	}

	void VertexArray::AddBuffer(const rxogl::VertexBuffer& vb, const rxogl::BufferLayout& layout)
	{
		Bind();
		vb.Bind();
		const auto& elements = layout.GetElements();
		unsigned int offset = 0;
		for (unsigned int i = 0; i < elements.size(); i++)
		{
			const auto& element = elements[i];

			std::cout << element.count << std::endl;

			GLCall(glVertexAttribPointer(i, element.count, element.type,
				element.normalized, layout.GetStride(), (const void*)offset));
			GLCall(glEnableVertexAttribArray(i));

			offset += element.count * rxogl::BufferElement::GetSizeOfType(element.type);
			//offset += element.count * element.type; // type doubles as both type name and size
		}
	}

	void VertexArray::Bind() const
	{
		GLCall(glBindVertexArray(m_RendererID));
	}

	void VertexArray::Unbind() const
	{
		GLCall(glBindVertexArray(0));
	}
}