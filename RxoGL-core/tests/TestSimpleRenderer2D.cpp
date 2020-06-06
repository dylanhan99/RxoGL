#include "TestSimpleRenderer2D.h"
#include "../vendor/imgui/imgui.h"

namespace tests
{
	TestSimpleRenderer2D::TestSimpleRenderer2D()
	{
		m_Shader = new Shader("res/shaders/basic.vert", "res/shaders/basic.frag");
		sprite = new rxogl::StaticSprite(glm::vec3(100, 100, 0), glm::vec2(50, 50), glm::vec4(0.609f, 0.115f, 0.436f, 1), *m_Shader);
		sprite2 = new rxogl::StaticSprite(glm::vec3(200, 100, 0), glm::vec2(50, 50), glm::vec4(0.609f, 0.115f, 0.436f, 1), *m_Shader);
	}

	TestSimpleRenderer2D::~TestSimpleRenderer2D()
	{
		delete m_Shader;
		delete sprite;
		delete sprite2;
	}

	void TestSimpleRenderer2D::OnUpdate(float deltaTime)
	{
	}

	void TestSimpleRenderer2D::OnRender()
	{
		rxogl::SimpleRenderer2D renderer;
		renderer.Submit(sprite);
		renderer.Submit(sprite2);
		renderer.Flush();
		//GLCall(glClearColor(m_Color[0], m_Color[1], m_Color[2], m_Color[3]));
		//GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void TestSimpleRenderer2D::OnImguiRender()
	{

	}
}