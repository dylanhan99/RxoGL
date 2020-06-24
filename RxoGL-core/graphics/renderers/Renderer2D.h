#pragma once

#include <gl/glew.h>
#include <vector>
//#include "../renderables/Renderable2D.h"
#include "../../ConstantsRxogl.h"

namespace rxogl
{
	class Renderable2D;
	class Renderer2D
	{
	protected:
		std::vector<glm::mat4> m_TransformationStack;
		const glm::mat4* m_TransformationStackBack;

		Renderer2D()
		{
			m_TransformationStack.push_back(glm::mat4(1.0f));
			m_TransformationStackBack = &m_TransformationStack.back();
		}
	public:
		void Push(const glm::mat4& matrix, bool override = false)
		{
			if (override)
				m_TransformationStack.push_back(matrix);
			else
				m_TransformationStack.push_back(m_TransformationStack[m_TransformationStack.size() - 1] * matrix);

			m_TransformationStackBack = &m_TransformationStack.back();
		}

		void Pop()
		{
			// To avoid popping the identity matrix
			if (m_TransformationStack.size() > 1)
			{
				m_TransformationStack.pop_back();
				m_TransformationStackBack = &m_TransformationStack.back();
			}
		}

		virtual void Begin() {}
		virtual void Submit(const Renderable2D* renderable) = 0;
		virtual void DrawString(const std::string text, constants::rxoPosition position, const constants::rxoColor color) {}
		virtual void End() {}
		virtual void Flush() = 0;
	//public:
	//	void Clear() const;
	//	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	};
}