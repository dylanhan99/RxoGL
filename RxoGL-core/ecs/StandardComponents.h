#pragma once
#include "ECS.h"
#include <functional>
#include <unordered_map>
#include "../graphics/textures/TextureManager.h"
#include "../Event.h"

namespace rxogl { 
	//class TextureData;
	namespace ecs {

	class Transform : public Component
	{
	private:
		glm::vec4 m_Position;
		glm::vec2 m_Size;

	public:
		Events::EventDispatcher OnPosChange;
		std::string m_OnPosChangeEvent;

		Transform(float x, float y, float z, float wid, float hei)
			: m_Position(x, y, z, 1), m_Size(wid, hei),
		m_OnPosChangeEvent("OnPosChange"){ }

		float x() { return m_Position.x; }
		float y() { return m_Position.y; }
		float z() { return m_Position.z; }

		void Update(float deltatime) override { }

		inline const constants::rxoPosition&	GetPosition()	const { return m_Position; }
		inline const glm::vec2&					GetSize()		const { return m_Size; }

		void SetPos(float x, float y, float z) 
		{ 
			m_Position = glm::vec4(x, y, z, 1); 
			OnPosChange.DispatchEvent(m_OnPosChangeEvent);
		}
		void SetPos(glm::vec3 newPos) 
		{ 
			m_Position = glm::vec4(newPos.x, newPos.y, newPos.z, 1); 
			OnPosChange.DispatchEvent(m_OnPosChangeEvent);
		}
	};

	class RectTransform : public Transform
	{
	private:
		glm::vec2 m_Size;
	public:
		inline const glm::vec2& GetSize() const { return m_Size; }
	};

	class Texture : public RenderableComponent
	{
		struct TexCoords
		{
			glm::vec2 bl, br, tr, tl;
		};
	private:
		std::shared_ptr<TextureData> m_TextureDat;
		TexCoords m_TexCoords;
		std::unordered_map<std::string, TexCoords> m_TexCoordsCache;
		constants::rxoColor m_Color;
		bool m_IsTextureSheet;
	public:
		Texture(const std::string& textureName, const std::string& filePath, float r, float g, float b, float a, bool isTextureSheet = false);
		Texture(float r, float g, float b, float a, std::size_t numSides = 4)
			: m_TextureDat(NULL), m_TexCoords({ glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 1.0f) }),
			m_IsTextureSheet(false), m_Color(r, g, b, a) { }
		~Texture() {}

		void Bind(unsigned int slot = 0) const {   
			//GLCall(glActiveTexture(GL_TEXTURE0 + slot));
			//GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
			if (m_TextureDat)
				m_TextureDat->Bind(); 
		}
		void Unbind() const {
			if (m_TextureDat)
				m_TextureDat->Unbind();
		}
		void Add(std::string textureName, float bl_x, float bl_y, float w, float h) // For TextureSheet
		{
			switch (m_IsTextureSheet) {
			case true:
				bl_x /= m_TextureDat->m_Height;
				bl_y /= m_TextureDat->m_Width;
				w /=	m_TextureDat->m_Height;
				h /=	m_TextureDat->m_Width;
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

		inline bool HasTexture() const
		{
			if (m_TextureDat != NULL)
				return true;
			return false;
		}
		inline const unsigned int&		  GetTexID()  const { return m_TextureDat->m_RendererID; }
		inline const unsigned int&		  GetWidth()  const { return m_TextureDat->m_Width; }
		inline const unsigned int&		  GetHeight() const { return m_TextureDat->m_Height; }
		inline const constants::rxoColor& GetColor()  const { return m_Color; }
		inline const TexCoords& GetTexCoords()	const
		{
			switch (m_IsTextureSheet) {
			case true:
				if(!m_TexCoordsCache.empty()) 
					return m_TexCoordsCache.at(m_TextureName);
				break;
			default:
				return m_TexCoords;
			}
		}
	};

	class Label : public RenderableComponent
	{
	private:
		std::string m_Text;
		float m_Scale;
		std::string m_FontName;
		constants::rxoColor m_Color;
	public:
		Label(float scale, float r, float g, float b, float a, std::string text, std::string fontName)
			: m_Text(text), m_Scale(scale), m_FontName(fontName), m_Color(constants::rxoColor(r, g, b, a)) { }

		inline void EditText(std::string& newText) { m_Text = newText; }

		inline const std::string& GetFontName() const { return m_FontName; }
		inline const std::string& GetText()	const { return m_Text; }
		inline const float& GetScale()		const { return m_Scale; }
		inline const constants::rxoColor& GetColor() const { return m_Color; }

	};

	class RigidBody2D : public PhysicsComponent
	{
		enum BodyType { Dynamic, Kinematic, Static };
	private:
		BodyType m_BodyType;
		float m_Mass;
		float m_LinearDrag;
		float m_GravityScale;

		glm::vec2 m_Velocity;
	public:
		void Update(float deltatime) override { }
	};

	class Collider2D : public ColliderComponent
	{
	private:
		glm::vec2 m_Offset; // Collider offset from centre. Centre is simply transform.Position
		//glm::vec2 m_Size;	// Size of collider relative to ??
	public:
		Collider2D() : m_Offset(glm::vec2(0.f, 0.f)) { }
		void Init() override;
	};

	class BoxCollider2D : public Collider2D
	{
	public:
		glm::vec2 m_Min;
		glm::vec2 m_Max;

		BoxCollider2D() : m_Min(glm::vec2()), m_Max(m_Min)
		{ m_ColliderType = ColliderType::BoxCollider2D; }

		void Init() override
		{
			Collider2D::Init();
			m_Entity->AddCollider(m_Entity->GetComponent<BoxCollider2D>());
			UpdateMinMax();
			auto transform = m_Entity->GetComponent<ecs::Transform>();
			transform->OnPosChange.RegisterEvent
			(new Events::Event<>(transform->m_OnPosChangeEvent, std::bind(&BoxCollider2D::UpdateMinMax, this)));
		}

		void UpdateMinMax()
		{
			auto transform = m_Entity->GetComponent<ecs::Transform>();
			m_Min = glm::vec2(transform->x(), transform->y());
			m_Max = glm::vec2(transform->x() + transform->GetSize().x, transform->y() + transform->GetSize().y);
		}

		bool ResolveCollision(const ColliderComponent& other) override;
	};

	class PolygonCollider2D : public Collider2D
	{
		std::vector<glm::vec3> m_Vertices;
	};

	class CircleCollider2D : public Collider2D
	{
	public:
		float m_Radius;

		CircleCollider2D(float rad)
		{
			m_ColliderType = ColliderType::CircleCollider2D;
			m_Radius = rad;
		}
	};

} }