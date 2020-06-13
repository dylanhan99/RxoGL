#pragma once
#include "Test.h"

#include <vector>
#include "../graphics/renderers/BatchRenderer2D.h"
#include "../graphics/renderables/StaticSprite.h"
#include "../graphics/renderables/Sprite.h"

#include "../graphics/layers/TileLayer.h"
#include "../graphics/layers/Group.h"
#include "../graphics/Texture.h"

namespace tests
{
	class TestGroups : public Test
	{
	private:
		Shader* m_Shader;
		rxogl::Group* buttonGroup;
		rxogl::Renderable2D* sprButton;
		rxogl::Renderable2D* sprText;
		glm::vec3 m_Translation;


		rxogl::TileLayer* layer;
		rxogl::Texture m_OWTexture;
	public:
		TestGroups();
		~TestGroups();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImguiRender() override;


	};
}