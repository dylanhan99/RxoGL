#include "MainScene.h"

namespace Game { namespace Scenes {
		MainScene::MainScene()
			: m_Camera(960 / 540, true)
		{
			rxogl::Application::GetInstance()->GetFontManager().RegisterFont("arial", "../res/fonts/arial.ttf");
			rxogl::Application::GetInstance()->GetFontManager().RegisterFont("droid", "../res/fonts/DroidSans.ttf");
			rxogl::Application::GetInstance()->GetFontManager().RegisterFont("matsura", "../res/fonts/MATURASC.TTF");
			rxogl::Application::GetInstance()->GetFontManager().RegisterFont("joker", "../res/fonts/JOKERMAN.TTF");
			rxogl::Application::GetInstance()->GetFontManager().RegisterFont("kuntsler", "../res/fonts/KUNSTLER.TTF");

			rxogl::ecs::Entity2D* obj = new rxogl::ecs::Entity2D();
			obj->AddComponent<rxogl::ecs::Transform>(100.f, 100.f, 0.f, 30.f, 30.f);
			obj->AddComponent<rxogl::ecs::Texture>("0", "../res/textures/abcSheet.png", 0.5f, 0.5f, 1.f, 1.f, true);
			obj->GetComponent<rxogl::ecs::Texture>().Add("0", 0, 0, 8, 8);
			obj->GetComponent<rxogl::ecs::Texture>().Add("1", 8, 0, 8, 8);
			obj->GetComponent<rxogl::ecs::Texture>().Add("2", 8, 8, 8, 8);

			rxogl::ecs::Entity2D* obj2 = new rxogl::ecs::Entity2D();
			obj2->AddComponent<rxogl::ecs::Transform>(5.f, 5.f, 0.f, 10.f, 30.f);
			obj2->AddComponent<rxogl::ecs::Texture>(1.f, 0.5f, 0.3f, 1.f);

			rxogl::ecs::Entity2D* obj3 = new rxogl::ecs::Entity2D();
			obj3->AddComponent<rxogl::ecs::Transform>(5.f, 5.f, 0.f, 10.f, 30.f);
			obj3->AddComponent<rxogl::ecs::Label>(1.f, 0.5f, 0.5f, 1.f, 1.f, "wtf man render pls", "arial");

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

			m_Fps = "4";

			m_Layer->Add(obj);
			m_Layer->Add(obj2);
			m_Layer->Add(obj3);

			AddLayer(m_Layer);

			//glm::mat4 transform = glm::rotate(glm::radians(20.f), glm::vec3(0, 0, 1));
			//transform = glm::translate(transform, glm::vec3(0, 450, 0));
			//glm::mat4 transform = glm::translate(glm::vec3(0, 450, 0));
			//transform = glm::rotate(transform, glm::radians(20.f), glm::vec3(0, 0, 1));
			//fpsGroup = new rxogl::Group(transform);
			//fpsGroup->Add(new rxogl::Sprite(0, 0, 0, 100, 50, textures[1], ""));
			//fpsGroup->Add(new rxogl::Label(10, 10, 1, rxogl::constants::rxoColor(0.5, 0.5, 1, 1), m_Fps, "arial"));
			//fpsGroup->Add(new rxogl::Label(100, 10, 1, rxogl::constants::rxoColor(0.5, 0.5, 1, 1), "the quick brown fox jumps over the lazy dog!", "matsura"));
			//fpsGroup->Add(new rxogl::Label(100, -40, 1, rxogl::constants::rxoColor(0.5, 0.5, 1, 1), "the quick brown fox jumps over the lazy dog!", "joker"));
			//fpsGroup->Add(new rxogl::Label(100, -90, 1, rxogl::constants::rxoColor(0.5, 0.5, 1, 1), "the quick brown fox jumps over the lazy dog!", "kuntsler"));
			//m_UILayer->Add(fpsGroup);


			//AddLayer(m_TileLayer);
			//AddLayer(m_UILayer);
		}

		MainScene::~MainScene()
		{
			Scene::~Scene();
		}

		void MainScene::OnUpdate(float deltatime)
		{
			// Update all entities and components
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
			ImGui::SliderFloat3("Layer1", &m_Translation.x, 0.0f, 960.0f);
		}
	}
}