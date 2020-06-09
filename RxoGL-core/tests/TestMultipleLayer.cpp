#include "TestMultipleLayer.h"
#include "../vendor/imgui/imgui.h"

namespace tests
{
	TestMultipleLayer::TestMultipleLayer()
	{
		m_Shader1 = new Shader("res/shaders/basic.vert", "res/shaders/basic.frag");
		m_Shader2 = new Shader("res/shaders/basic.vert", "res/shaders/basic.frag");
		layer1 = new rxogl::TileLayer(m_Shader1);
		layer2 = new rxogl::TileLayer(m_Shader2);

		float size = 6;
		float width = size - 1;
		for (float y = 0; y < 540; y += size)
		{
			for (float x = 0; x < 960; x += size)
			{
				sprites.push_back(new rxogl::Sprite(glm::vec3(x, y, 0), 
													glm::vec2(width, width),
													glm::vec4(rand() % 1000 / 1000.f, 0.0f, 0.5f, 1)));
			}
		}

		m_Shader1->Bind();
		for (int i = 0; i < sprites.size(); i++)
			layer1->Add(sprites[i]);

		m_Shader2->Bind();
		sprite1 = new rxogl::Sprite(glm::vec3(50, 50, 0),
								glm::vec2(50, 50),
								glm::vec4(rand() % 1000 / 1000.f, 0.0f, 0.5f, 1));
		sprite2 = new rxogl::Sprite(glm::vec3(200, 50, 0),
								glm::vec2(50, 50),
								glm::vec4(0.0f, rand() % 1000 / 1000.f, 0.5f, 1));
		layer2->Add(sprite1);
		layer2->Add(sprite2);
		m_TranslationA = sprite1->GetPosition();
		m_TranslationB = sprite2->GetPosition();
	}

	TestMultipleLayer::~TestMultipleLayer()
	{
		// deleting shaders and renderables is handled in layer destructor already
		delete layer1;
		delete layer2;
	}

	void TestMultipleLayer::OnUpdate(float deltaTime)
	{

	}

	void TestMultipleLayer::OnRender()
	{
		glm::mat4 proj = glm::ortho(0.f, 960.f, 0.f, 540.f, -1.0f, 1.0f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

		// Layer1
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
			glm::mat4 mvp = proj * view * model; // This should be handled in Layer. See comment in layer.cpp
			m_Shader1->SetUniformMat4f("u_MVP", mvp);
			layer1->Render();
		}

		// Layer2
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);

			glm::mat4 mvp = proj * view * model; // This should be handled in Layer. See comment in layer.cpp

			m_Shader2->SetUniformMat4f("u_MVP", mvp);// This should be handled in Layer. See comment in layer.cpp
			layer2->Render();
		}
	}

	void TestMultipleLayer::OnImguiRender()
	{
		ImGui::SliderFloat3("Translation A", &m_TranslationA.x, 0.0f, 960.0f);
		ImGui::SliderFloat3("Translation B", &m_TranslationB.x, 0.0f, 960.0f);
	}
}