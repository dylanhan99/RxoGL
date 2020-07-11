#pragma once
#include "Scene.h"
#include "rxogl.h"

#include "graphics/layers/TileLayer.h"
#include "graphics/layers/UILayer.h"

#include "graphics/CameraOrthoController.h"

namespace rxogl { namespace scenes {

	class SceneTest : public Scene
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

		CameraOrthoController m_Camera;

		std::string m_Fps;
	public:
		SceneTest();
		~SceneTest() override;

		void OnUpdate(float deltatime) override;
		void OnRender() override;
		void OnImguiRender() override;
	};

} }