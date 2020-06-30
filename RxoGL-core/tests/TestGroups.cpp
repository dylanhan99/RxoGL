#include "TestGroups.h"
#include "../vendor/imgui/imgui.h"
#include "../graphics/renderables/Label.h"

namespace tests
{
	TestGroups::TestGroups()
		: m_OWTexture("res/textures/a.png"), m_OCTexture("res/textures/b.png"), m_FOTexture("res/textures/c.png")
	{
		rxogl::Texture* textures[] =
		{
			&m_OWTexture,
			&m_OCTexture,
			&m_FOTexture
		};

		m_Shader = new Shader("res/shaders/basic.vert", "res/shaders/basic.frag");
		layer = new rxogl::TileLayer(m_Shader);

		m_Shader->Bind();
		int texIDs[32];
		for (int i = 0; i < 32; i++)
			texIDs[i] = i;
		m_Shader->SetUniform1iv("u_Textures", 32, texIDs);

		float size = 20;
		float width = size;
		for (float y = 0; y < 540; y += size)
		{
			for (float x = 0; x < 960; x += size)
			{
				if (rand() % 4 == 0)
				{
					layer->Add(new rxogl::Sprite(x, y, 0,
						width, width,
						textures[rand() % 3]));
				}
				else
				{
					layer->Add(new rxogl::Sprite(x, y, 0,
						width, width,
						glm::vec4(rand() % 1000 / 1000.f, 0, 0.7f, 1)));
				}
			}
		}

		layer->Add(new rxogl::Label(40, 40, 1.f, rxogl::constants::rxoColor(0, 1, 0, 1), "The Quick Brown Fox Jumps Over The Moon!"));

		/*sprButton = new rxogl::Sprite(0, 0, 0,
			100, 50,
			glm::vec4(rand() % 1000 / 1000.f, 0.0f, 0.7f, 1));

		sprText = new rxogl::Sprite(10, 10, 0,
			80, 30,
			glm::vec4(0.0f, rand() % 1000 / 1000.f, 0.7f, 1));
		
		glm::mat4 transform = glm::rotate(glm::radians(45.f), glm::vec3(0, 0, 1));
		transform = glm::translate(transform, glm::vec3(500, -100, 0));
		rxogl::Group* ManyButtons = new rxogl::Group(transform);

		buttonGroup = new rxogl::Group(glm::translate(glm::vec3(0,0,0)));
		buttonGroup->Add(sprButton);
		buttonGroup->Add(sprText);

		ManyButtons->Add(new rxogl::Sprite(0.f, 0.f, 0.f, 200.f, 200.f, glm::vec4(0.5f, rand() % 1000 / 1000.f, 0.7f, 1)));
		ManyButtons->Add(buttonGroup);
		layer->Add(ManyButtons);

		m_Translation = ManyButtons->GetPosition();

		m_OWTexture.Bind(1);*/
	}

	TestGroups::~TestGroups()
	{
		// deleting shaders and renderables is handled in layer destructor already
		delete layer;
	}

	void TestGroups::OnUpdate(float deltaTime)
	{
	}

	void TestGroups::OnRender()
	{
		glm::mat4 proj = glm::ortho(0.f, 960.f, 0.f, 540.f, -1.0f, 1.0f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

		// Layer1
		{
			m_Shader->Bind();
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translation);

			glm::mat4 mvp = proj * view * model; // This should be handled in Layer. See comment in layer.cpp
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			layer->Render();
		}
	}

	void TestGroups::OnImguiRender()
	{
		ImGui::SliderFloat3("Layer1", &m_Translation.x, 0.0f, 960.0f);
	}
}