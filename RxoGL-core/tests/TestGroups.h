#pragma once
#include "Test.h"

#include <vector>
#include "../graphics/renderers/BatchRenderer2D.h"
#include "../graphics/renderables/StaticSprite.h"
#include "../graphics/renderables/Sprite.h"
#include "../graphics/renderables/Label.h"

#include "../graphics/layers/TileLayer.h"
#include "../graphics/layers/UILayer.h"
#include "../graphics/layers/Group.h"
#include "../graphics/textures/TextureSheet.h"

namespace tests
{
	class TestGroups : public Test
	{
	private:
		Shader* m_Shader1;
		Shader* m_Shader2;
		rxogl::Group* buttonGroup;
		rxogl::Group* fpsGroup;
		rxogl::Renderable2D* sprButton;
		rxogl::Renderable2D* sprText;
		glm::vec3 m_Translation;

		rxogl::TileLayer* m_TileLayer;
		rxogl::UILayer* m_UILayer;
		rxogl::Texture m_OWTexture, m_OCTexture, m_FOTexture;
		rxogl::TextureSheet m_TexSheet;

		std::string m_Fps;
	public:
		TestGroups();
		~TestGroups();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImguiRender() override;


	};
}