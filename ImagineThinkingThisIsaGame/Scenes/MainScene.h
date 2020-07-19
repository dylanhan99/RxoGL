#pragma once
#include "rxogl.h"
#include "../Layers/UILayer.h"
#include "../Camera/CameraOrthoController.h"

namespace Game { namespace Scenes {

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

			Layers::UILayer* m_TileLayer;
			Layers::UILayer* m_UILayer;
			rxogl::Texture m_OWTexture, m_OCTexture, m_FOTexture;
			rxogl::TextureSheet m_TexSheet;

			Camera::CameraOrthoController m_Camera;

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