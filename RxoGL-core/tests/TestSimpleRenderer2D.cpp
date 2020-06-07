#include "TestSimpleRenderer2D.h"
#include "../vendor/imgui/imgui.h"

namespace tests
{
	TestSimpleRenderer2D::TestSimpleRenderer2D()
	{
		m_Shader = new Shader("res/shaders/basic.vert", "res/shaders/basic.frag");

		float size = 30;
		float width = size - 5;
		for (float y = 0; y < 540; y += size)
		{
			for (float x = 0; x < 960; x += size)
			{
				sprites.push_back(new rxogl::StaticSprite(glm::vec3(x, y, 0),
														  glm::vec2(width, width),
														  glm::vec4(rand() % 1000 / 1000.f, rand() % 1000 / 1000.f, rand() % 1000 / 1000.f, 1)
														  , *m_Shader));
			}
		}

	}

	TestSimpleRenderer2D::~TestSimpleRenderer2D()
	{
		delete m_Shader;
		for (rxogl::Renderable2D* s : sprites)
		{
			delete s;
		}

	}

	void TestSimpleRenderer2D::OnUpdate(float deltaTime)
	{
	}

	void TestSimpleRenderer2D::OnRender()
	{
		rxogl::SimpleRenderer2D renderer;
		for (int i = 0; i < sprites.size(); i++)
		{
			renderer.Submit(sprites[i]);
		}
		renderer.Flush();
		//GLCall(glClearColor(m_Color[0], m_Color[1], m_Color[2], m_Color[3]));
		//GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void TestSimpleRenderer2D::OnImguiRender()
	{

	}
}