#include "TestSimpleBatchRenderer2D.h"
#include "../vendor/imgui/imgui.h"

namespace tests
{
	TestSimpleBatchRenderer2D::TestSimpleBatchRenderer2D()
	{
		m_Shader = new Shader("res/shaders/basic.vert", "res/shaders/basic.frag");
		sprite  = new rxogl::Sprite(glm::vec3(100, 100, 0), glm::vec2(50, 50), glm::vec4(0.609f, 0.115f, 0.436f, 1)/*, *m_Shader*/);
		sprite2 = new rxogl::Sprite(glm::vec3(200, 100, 0), glm::vec2(50, 50), glm::vec4(0.609f, 0.115f, 0.436f, 1)/*, *m_Shader*/);

	}

	TestSimpleBatchRenderer2D::~TestSimpleBatchRenderer2D()
	{
		delete m_Shader;
		delete sprite;
		delete sprite2;
	}

	void TestSimpleBatchRenderer2D::OnUpdate(float deltaTime)
	{

	}

	void TestSimpleBatchRenderer2D::OnRender()
	{
		rxogl::BatchRenderer2D renderer;
		renderer.Begin();
		renderer.Submit(sprite);
		renderer.Submit(sprite2);
		renderer.End();
		renderer.Flush();
	}

	void TestSimpleBatchRenderer2D::OnImguiRender()
	{

	}
}