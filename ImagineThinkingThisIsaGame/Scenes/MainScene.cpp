#include "MainScene.h"

namespace Game { namespace Scenes {
		MainScene::MainScene()
			//: m_Camera(960 / 540, true)
		{
			rxogl::NativeScriptManager::GetInstance();
			playerPos = glm::vec3(0.f, 0.f, 0.f);

			rxogl::Application::GetInstance()->GetFontManager().RegisterFont("arial", "../res/fonts/arial.ttf");

			player = new rxogl::ecs::Entity2D("player");
			player->AddComponent<rxogl::ecs::Transform>(playerPos.x, playerPos.y, playerPos.z, 10.f, 30.f);
			player->AddComponent<rxogl::ecs::Texture>("player", "../res/textures/player.png", 1.f, 1.f, 1.f, 1.f);
			player->AddComponent<rxogl::ecs::BoxCollider2D>();
			player->AddComponent<rxogl::ecs::NativeScriptComponent>()->
				Bind<Script::PlayerControlScript>();
			player->AddComponent<rxogl::ecs::NativeScriptComponent>()->
				Bind<Script::PlayerCollisionScript>();

			camera = new rxogl::ecs::Entity2D();
			camera->AddComponent<rxogl::ecs::NativeScriptComponent>()->
				Bind<Camera::CameraMovementScript>(*(player->GetComponent<rxogl::ecs::Transform>()), 960 / 540, true);
			
			rxogl::ecs::Entity2D* ground = new rxogl::ecs::Entity2D("ground");
			ground->AddComponent<rxogl::ecs::Transform>(-960/2, -540/2, 0.f, 960.f, 540.f/2);
			ground->AddComponent<rxogl::ecs::Texture>("ground", "../res/textures/ground.png", 1.f, 1.f, 1.f, 1.f);
			ground->AddComponent<rxogl::ecs::BoxCollider2D>();

			m_Shader1 = std::make_shared<Shader>("../res/shaders/basic.vert", "../res/shaders/basic.frag");
			m_Layer = new Layers::UILayer(m_Shader1);

			m_Shader1->Bind();
			int texIDs[32];
			for (int i = 0; i < 32; i++)
				texIDs[i] = i;
			m_Shader1->SetUniform1iv("u_Textures", 32, texIDs);

			m_Layer->Add(camera);
			m_Layer->Add(player);
			m_Layer->Add(ground);

			AddLayer(m_Layer);
			rxogl::NativeScriptManager::GetInstance()->Init();
		}

		MainScene::~MainScene()
		{
			Scene::~Scene();
		}

		void MainScene::OnUpdate(float deltatime)
		{
			// Update all entities and components
		}

		void MainScene::OnRender()
		{
			// Update scene variables before rendering layers ^^^
			Scene::OnRender();
		}

		void MainScene::OnImguiRender()
		{
			ImGui::SliderFloat3("Trans x", &m_Translation.x, -100.0f, 100.0f);
			ImGui::SliderFloat3("Player x", &playerPos.x, -100.0f, 100.0f);
		}
	}
}