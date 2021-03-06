#pragma once
#include "Renderer2D.h"

#include "../../vendor/FreeType/FreeType-gl.h"
#include "../buffers/VertexArray.h"
#include "../buffers/Buffer.h"
#include "../renderables/Sprite.h"
#include "../../ConstantsRxogl.h"
#include "../Font.h"

namespace rxogl
{
#define RENDERER_MAX_SPRITES	42500
#define RENDERER_VERTEX_SIZE	sizeof(constants::Vertex)
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE	RENDERER_MAX_SPRITES * 6

	class TextRenderer : public Renderer2D
	{
	private:
		VertexArray m_VAO;
		VertexBuffer m_VBO;
		IndexBuffer* m_IBO;
		GLsizei m_IndexCount;
		constants::TextVertex* m_Buffer;

		std::vector<unsigned int> m_TextureSlots;

	public:
		TextRenderer();
		~TextRenderer();

		void Begin() override;
		void Submit(const Renderable2D* renderable) override;
		//virtual void SubmitString(const Renderable2D* renderable) override;
		void End() override;
		void Flush() override;
	};

}