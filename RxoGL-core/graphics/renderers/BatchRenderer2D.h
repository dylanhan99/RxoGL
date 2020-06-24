#pragma once
#include "../../vendor/FreeType/FreeType-gl.h"

#include "../buffers/VertexArray.h"
#include "../buffers/Buffer.h"
#include "../../ConstantsRxogl.h"
#include "Renderer2D.h"
#include "../renderables/Sprite.h"

namespace rxogl
{
#define RENDERER_MAX_SPRITES	42500
#define RENDERER_VERTEX_SIZE	sizeof(constants::Vertex)
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE	RENDERER_MAX_SPRITES * 6

	class BatchRenderer2D : public Renderer2D
	{
	private:
		VertexArray m_VAO;
		VertexBuffer m_VBO;
		IndexBuffer* m_IBO;
		GLsizei m_IndexCount;
		constants::Vertex* m_Buffer;

		std::vector<unsigned int> m_TextureSlots;
		
	public:
		BatchRenderer2D();
		~BatchRenderer2D();

		void Begin() override;
		void Submit(const Renderable2D* renderable) override;
		virtual void DrawString(const std::string text, constants::rxoPosition position, const constants::rxoColor color) override;
		void End() override;
		void Flush() override;
	};
}