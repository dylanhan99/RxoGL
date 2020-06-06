#pragma once
#include "VertexArray.h"
#include "Buffer.h"
#include "ConstantsRxogl.h"
#include "Renderer.h"

namespace rxogl
{
#define RENDERER_MAX_SPRITES	10000
#define RENDERER_VERTEX_SIZE	sizeof(constants::Vertex)
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE	RENDERER_VERTEX_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE	RENDERER_VERTEX_SIZE * 6

	class BatchRenderer2D : Renderer
	{
	private:
		VertexArray m_VAO;
		VertexBuffer m_VBO;
		IndexBuffer* m_IBO;
		GLsizei m_IndexCount;

		constants::Vertex* m_Buffer;

	public:
		BatchRenderer2D();
		~BatchRenderer2D();

		void Begin();
		void Submit(Renderable2D* renderable) override;
		void End();
		void Flush() override;
	};
}