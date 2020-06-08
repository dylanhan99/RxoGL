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
		m_Shader2->Bind();
	}

	TestMultipleLayer::~TestMultipleLayer()
	{
		delete m_Shader1;
		delete m_Shader2;
		delete layer1;
		delete layer2;
		for (rxogl::Renderable2D* s : sprites)
		{
			delete s;
		}
	}

	void TestMultipleLayer::OnUpdate(float deltaTime)
	{

	}

	void TestMultipleLayer::OnRender()
	{
		glm::mat4 proj = glm::ortho(0.f, 960.f, 0.f, 540.f, -1.0f, 1.0f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		glm::mat4 mvp = proj * view * model; // This should be handled in Layer. See comment in layer.cpp
		m_Shader1->SetUniformMat4f("u_MVP", mvp);
		m_Shader2->SetUniformMat4f("u_MVP", mvp);// This should be handled in Layer. See comment in layer.cpp

		for (int i = 0; i < sprites.size(); i++)
			layer1->Add(sprites[i]);
		layer1->Render();
	}

	void TestMultipleLayer::OnImguiRender()
	{

	}
}