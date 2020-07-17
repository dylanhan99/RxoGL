#include "MainScene.h"
#include "vendor/imgui/imgui.h"

namespace Game {
	namespace scenes {
		MainScene::MainScene()
			: m_OWTexture("../res/textures/a.png"), m_OCTexture("../res/textures/b.png"), m_FOTexture("../res/textures/c.png"), m_TexSheet("../res/textures/abcSheet.png"),
			m_Camera(960 / 540, true)
		{
			m_TexSheet.Add("0", 0, 0, 8, 8);
			m_TexSheet.Add("1", 8, 0, 8, 8);
			m_TexSheet.Add("2", 8, 8, 8, 8);
			rxogl::Texture* textures[] =
			{
				&m_OWTexture,
				&m_OCTexture,
				&m_FOTexture
			};

			m_Shader1 = new Shader("../res/shaders/basic.vert", "../res/shaders/basic.frag");
			m_Shader2 = new Shader("../res/shaders/basic.vert", "../res/shaders/basic.frag");
			m_TileLayer = new UILayer(m_Shader1);
			m_UILayer = new UILayer(m_Shader2);

			m_Shader1->Bind();
			int texIDs[32];
			for (int i = 0; i < 32; i++)
				texIDs[i] = i;
			m_Shader1->SetUniform1iv("u_Textures", 32, texIDs);

			float size = 20;
			float width = size;
			for (float y = 0; y < 540; y += size)
			{
				for (float x = 0; x < 960; x += size)
				{
					if (rand() % 4 == 0)
					{
						m_TileLayer->Add(new rxogl::Sprite(x, y, 0,
							width, width,
							&m_TexSheet,
							std::to_string(rand() % 3)));
					}
					else
					{
						m_TileLayer->Add(new rxogl::Sprite(x, y, 0,
							width, width,
							glm::vec4(rand() % 1000 / 1000.f, 0, 0.7f, 1)));
					}
				}
			}

			m_Shader2->Bind();
			m_Shader2->SetUniform1iv("u_Textures", 32, texIDs);

			m_Fps = "4";

			//glm::mat4 transform = glm::rotate(glm::radians(20.f), glm::vec3(0, 0, 1));
			//transform = glm::translate(transform, glm::vec3(0, 450, 0));
			glm::mat4 transform = glm::translate(glm::vec3(0, 450, 0));
			transform = glm::rotate(transform, glm::radians(20.f), glm::vec3(0, 0, 1));
			fpsGroup = new rxogl::Group(transform);
			fpsGroup->Add(new rxogl::Sprite(0, 0, 0, 100, 50, textures[1], ""));
			fpsGroup->Add(new rxogl::Label(10, 10, 1, rxogl::constants::rxoColor(0.5, 0.5, 1, 1), m_Fps));
			m_UILayer->Add(fpsGroup);

		}

		MainScene::~MainScene()
		{
			Scene::~Scene();
		}

		void MainScene::OnUpdate(float deltatime)
		{
			m_Camera.OnUpdate(deltatime);
		}

		void MainScene::OnRender()
		{
			// Update scene variables before rendering layers ^^^
			//glm::mat4 proj = glm::ortho(0.f, 960.f, 0.f, 540.f, -1.0f, 1.0f);
			//glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

			const glm::mat4& pv = m_Camera.GetCamera().GetProjectionViewMatrix();
			// m_TileLayer
			{
				m_Shader1->Bind();
				glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translation);

				//glm::mat4 mvp = proj * view * model; // This should be handled in Layer. See comment in layer.cpp
				glm::mat4 mvp = pv * model;
				m_Shader1->SetUniformMat4f("u_MVP", mvp);
				m_TileLayer->Render();
			}
			// m_UILayer
			{
				m_Shader2->Bind();
				glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

				glm::mat4 mvp = pv * model;
				m_Shader2->SetUniformMat4f("u_MVP", mvp);
				m_UILayer->Render();
			}

			Scene::OnRender();
		}

		void MainScene::OnImguiRender()
		{
			ImGui::SliderFloat3("Layer1", &m_Translation.x, 0.0f, 960.0f);
		}

	}
}