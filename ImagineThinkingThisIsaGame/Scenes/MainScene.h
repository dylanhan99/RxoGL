#pragma once
#include "rxogl.h"
#include "../Layers/UILayer.h"
#include "../Camera/CameraOrthoController.h"

namespace Game { namespace Scenes {

		class MainScene : public rxogl::scenes::Scene
		{
		private:
			std::shared_ptr<Shader> m_Shader1;
			std::shared_ptr<Shader> m_Shader2;
			rxogl::ecs::Entity2D* sprButton;
			rxogl::ecs::Entity2D* sprText;
			rxogl::ecs::Group* fpsGroup;
			glm::vec3 m_Translation;

			Layers::UILayer* m_Layer;

			//Camera::CameraOrthoController m_Camera;

			std::string m_Fps;
			rxogl::ecs::Entity2D* camera;
			rxogl::ecs::Entity2D* player;
			glm::vec3 playerPos;
		public:
			MainScene();
			~MainScene() override;

			void OnUpdate(float deltatime) override;
			void OnRender() override;
			void OnImguiRender() override;
		};

	}
}