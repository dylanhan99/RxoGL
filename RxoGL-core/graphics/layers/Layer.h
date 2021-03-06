#pragma once
//#include "../renderers/Renderer2D.h"
//#include "../renderables/Entity2D.h"
#include "../../ConstantsRxogl.h"
#include "../../ecs/ECS.h"

class Shader;
namespace rxogl
{
	class Renderer2D;
	class Layer
	{
	protected:
		std::shared_ptr<Renderer2D> m_Renderer;
		std::shared_ptr<Shader> m_Shader;
		ecs::EntityManager m_EntityManager;
		glm::mat4 m_ProjectionMatrix;

		Layer(std::shared_ptr<Renderer2D> renderer, std::shared_ptr<Shader> shader, glm::mat4 matrix);
	public:
		virtual ~Layer();
		virtual void Add(ecs::Entity* entity);
		virtual void Update(float deltatime);
		virtual void Render();

		inline const std::shared_ptr<Renderer2D> GetRenderer() const { return m_Renderer; }
		inline const std::shared_ptr<Shader> GetShader() const { return m_Shader; }
		inline std::vector<std::shared_ptr<rxogl::ecs::Entity>> GetEntitiesTag(std::string tag) { return m_EntityManager.GetEntitiesTag(tag); }
	};
}