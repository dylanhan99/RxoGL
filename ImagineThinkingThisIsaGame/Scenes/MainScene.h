#pragma once
#pragma once
#include "Scene.h"
#include "rxogl.h"

#include "../Layers/UILayer.h"
#include "graphics/CameraOrthoController.h"

namespace Game {
	namespace scenes {

		class MainScene : public rxogl::scenes::Scene
		{
		private:
			Shader* m_Shader1;
			Shader* m_Shader2;
			rxogl::Group* buttonGroup;
			rxogl::Group* fpsGroup;
			rxogl::Renderable2D* sprButton;
			rxogl::Renderable2D* sprText;
			glm::vec3 m_Translation;

			UILayer* m_TileLayer;
			UILayer* m_UILayer;
			rxogl::Texture m_OWTexture, m_OCTexture, m_FOTexture;
			rxogl::TextureSheet m_TexSheet;

			rxogl::CameraOrthoController m_Camera;

			std::string m_Fps;
		public:
			MainScene();
			~MainScene() override;

			void OnUpdate(float deltatime) override;
			void OnRender() override;
			void OnImguiRender() override;
		};

	}
}