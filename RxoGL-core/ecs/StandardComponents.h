#pragma once
#include "ECS.h"
#include <unordered_map>
#include "../ConstantsRxogl.h"

namespace rxogl { 
	class TextureData;
	namespace ecs {

	class Transform : public Component
	{
	private:
		glm::vec4 m_Position;
		glm::vec2 m_Size;
	public:
		Transform() { Init(); }
		Transform(float x, float y, float z, float wid, float hei)
			: m_Position(x, y, z, 1), m_Size(wid, hei) { }

		float x() { return m_Position.x; }
		float y() { return m_Position.y; }
		float z() { return m_Position.z; }

		void Init() override
		{
			m_Position = glm::vec4(0, 0, 0, 1);
			m_Size = glm::vec2(20, 20);
		}

		void Update() override
		{

		}

		inline const constants::rxoPosition&	GetPosition()	const { return m_Position; }
		inline const glm::vec2&					GetSize()		const { return m_Size; }

		void SetPos(float x, float y, float z)
		{
			m_Position = glm::vec4(x, y, z, 1);
		}
	};

	class RectTransform : public Transform
	{
	private:
		glm::vec2 m_Size;
	public:
		inline const glm::vec2& GetSize()			const { return m_Size; }
	};

	class Texture : public Component
	{
		struct TexCoords
		{
			glm::vec2 bl, br, tr, tl;
		};
	private:
		TextureData* m_TextureDat;

		TexCoords m_TexCoords;
		std::unordered_map<std::string, TexCoords> m_TexCoordsCache;
		constants::rxoColor m_Color;
		bool m_IsTextureSheet;
	public:
		Texture(const std::string& filePath, float r, float g, float b, float a, bool isTextureSheet = false);
		Texture(float r, float g, float b, float a);
		~Texture();

		//void Load();
		void Bind(unsigned int slot = 0) const;
		void Unbind() const;

		void Add(std::string textureName, float bl_x, float bl_y, float w, float h) // For TextureSheet
		{
			switch (m_IsTextureSheet) {
			case true:
				bl_x /= m_Height;
				bl_y /= m_Width;
				w /= m_Height;
				h /= m_Width;
				m_TexCoordsCache[textureName] = TexCoords
				{
					glm::vec2(bl_x		, bl_y),	 // bl
					glm::vec2(bl_x + w	, bl_y),	 // br
					glm::vec2(bl_x + w	, bl_y + h), // tr
					glm::vec2(bl_x		, bl_y + h)  // tl 
				};
				break;
			default:
				break;
			}
		} 

		inline const unsigned int& GetTexID()		const { return m_RendererID; }
		inline const unsigned int& GetWidth()		const { return m_Width; }
		inline const unsigned int& GetHeight()		const { return m_Height; }
		inline const constants::rxoColor& GetColor() const { return m_Color; }

		inline const TexCoords& GetTexCoords()	const
		{
			switch (m_IsTextureSheet) {
			case true:
				return m_TexCoordsCache.at(m_Entity->GetTextureName());
				break;
			default:
				return m_TexCoords;
			}
		}
	};

	class Label : public Component
	{
	private:
		std::string m_Text;
		float m_Scale;
		std::string m_FontName;
		constants::rxoColor m_Color;
	public:
		Label(float scale, float r, float g, float b, float a, std::string text, std::string fontName);
		//void Submit(std::shared_ptr<Renderer2D> renderer) const override;

		inline void EditText(std::string newText) { m_Text = newText; }

		inline const std::string& GetText()	const { return m_Text; }
		inline const float& GetScale()		const { return m_Scale; }

	};
} }