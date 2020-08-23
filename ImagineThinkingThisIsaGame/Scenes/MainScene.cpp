#include "MainScene.h"

namespace Game { namespace Scenes {
		MainScene::MainScene()
			: m_Camera(960 / 540, true)
		{
			playerPos = glm::vec3(0.f, 0.f, 0.f);

			rxogl::Application::GetInstance()->GetFontManager().RegisterFont("arial", "../res/fonts/arial.ttf");
			rxogl::Application::GetInstance()->GetFontManager().RegisterFont("droid", "../res/fonts/DroidSans.ttf");
			rxogl::Application::GetInstance()->GetFontManager().RegisterFont("matsura", "../res/fonts/MATURASC.TTF");
			rxogl::Application::GetInstance()->GetFontManager().RegisterFont("joker", "../res/fonts/JOKERMAN.TTF");
			rxogl::Application::GetInstance()->GetFontManager().RegisterFont("kuntsler", "../res/fonts/KUNSTLER.TTF");

			//rxogl::ecs::Entity2D* obj = new rxogl::ecs::Entity2D();
			//obj->AddComponent<rxogl::ecs::Transform>(100.f, 100.f, 0.f, 30.f, 30.f);
			//obj->AddComponent<rxogl::ecs::Texture>("0", "../res/textures/abcSheet.png", 0.5f, 0.5f, 1.f, 1.f, true);
			//obj->GetComponent<rxogl::ecs::Texture>().Add("0", 0, 0, 8, 8);
			//obj->GetComponent<rxogl::ecs::Texture>().Add("1", 8, 0, 8, 8);
			//obj->GetComponent<rxogl::ecs::Texture>().Add("2", 8, 8, 8, 8);
			//
			//rxogl::ecs::Entity2D* obj2 = new rxogl::ecs::Entity2D();
			//obj2->AddComponent<rxogl::ecs::Transform>(5.f, 5.f, 0.f, 10.f, 30.f);
			//obj2->AddComponent<rxogl::ecs::Texture>(1.f, 0.5f, 0.3f, 1.f);
			//
			//rxogl::ecs::Entity2D* obj3 = new rxogl::ecs::Entity2D();
			//obj3->AddComponent<rxogl::ecs::Transform>(5.f, 5.f, 0.f, 10.f, 30.f);
			//obj3->AddComponent<rxogl::ecs::Label>(1.f, 0.5f, 0.5f, 1.f, 1.f, "59", "arial");

			player = new rxogl::ecs::Entity2D();
			player->AddComponent<rxogl::ecs::Transform>(playerPos.x, playerPos.y, playerPos.z, 10.f, 30.f);
			//player->AddComponent<rxogl::ecs::Texture>(1.f, 0.5f, 0.3f, 1.f);
			player->AddComponent<rxogl::ecs::Texture>("yo", "../res/textures/abcSheet.png", 1.f, 1.f, 1.f, 1.f);
			player->AddComponent<rxogl::ecs::BoxCollider2D>();
			
			rxogl::ecs::Entity2D* other = new rxogl::ecs::Entity2D();
			other->AddComponent<rxogl::ecs::Transform>(0.f, 0.f, 0.f, 10.f, 30.f);
			other->AddComponent<rxogl::ecs::Texture>(0.5f, 1.f, 0.3f, 1.f);
			other->AddComponent<rxogl::ecs::BoxCollider2D>();


			m_Shader1 = std::make_shared<Shader>("../res/shaders/basic.vert", "../res/shaders/basic.frag");
			m_Layer = new Layers::UILayer(m_Shader1);

			m_Shader1->Bind();
			int texIDs[32];
			for (int i = 0; i < 32; i++)
				texIDs[i] = i;
			m_Shader1->SetUniform1iv("u_Textures", 32, texIDs);

			//float size = 20;
			//float width = size;
			//for (float y = 0; y < 540; y += size)
			//{
			//	for (float x = 0; x < 960; x += size)
			//	{
			//		if (rand() % 4 == 0)
			//		{
			//			m_Layer->Add(new rxogl::Sprite(x, y, 0,
			//				width, width,
			//				&m_TexSheet,
			//				std::to_string(rand() % 3)));
			//		}
			//		else
			//		{
			//			m_Layer->Add(new rxogl::Sprite(x, y, 0,
			//				width, width,
			//				glm::vec4(rand() % 1000 / 1000.f, 0, 0.7f, 1)));
			//		}
			//	}
			//}

			//m_Shader2->Bind();
			//m_Shader2->SetUniform1iv("u_Textures", 32, texIDs);

			//glm::mat4 transform = glm::rotate(glm::radians(180.f), glm::vec3(0, 0, 1));
			//transform = glm::translate(transform, glm::vec3(0, 450, 0));
			//fpsGroup = new rxogl::ecs::Group(transform);
			//m_Layer->Add(fpsGroup);
			//m_Layer->Add(obj);
			//fpsGroup->Add(obj2);
			//fpsGroup->Add(obj3);

			m_Layer->Add(player);
			m_Layer->Add(other);

			AddLayer(m_Layer);
		}

		MainScene::~MainScene()
		{
			Scene::~Scene();
		}

		void MainScene::OnUpdate(float deltatime)
		{
			// Update all entities and components
			auto tran = player->GetComponent<rxogl::ecs::Transform>();
			player->GetComponent<rxogl::ecs::Transform>()->SetPos(playerPos);

			const glm::mat4& pv = m_Camera.GetCamera().GetProjectionViewMatrix();
			{
				m_Layer->GetShader()->Bind();
				glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translation);
				glm::mat4 mvp = pv * model;
				m_Layer->GetShader()->SetUniformMat4f("u_MVP", mvp);
			}
			//{
			//	m_UILayer->GetShader()->Bind();
			//	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
			//	glm::mat4 mvp = pv * model;
			//	m_UILayer->GetShader()->SetUniformMat4f("u_MVP", mvp);
			//}

			m_Camera.OnUpdate(deltatime);
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