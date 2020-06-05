#include "TestRenderer2D.h"
#include "../vendor/imgui/imgui.h"

namespace tests
{
	TestRenderer2D::TestRenderer2D()
		//:m_Shader("res/shaders/basic.vert", "res/shaders/basic.frag")
	{
		m_Shader = new Shader("res/shaders/basic.vert", "res/shaders/basic.frag");
		//sprite = std::make_unique<rxogl::Renderable2D>(glm::vec3(100, 100, 0), glm::vec2(50, 50), glm::vec4(0.609f, 0.115f, 0.436f, 1), m_Shader);
		sprite = new rxogl::Renderable2D(glm::vec3(100, 100, 0), glm::vec2(50, 50), glm::vec4(0.609f, 0.115f, 0.436f, 1), *m_Shader);
		sprite2 = new rxogl::Renderable2D(glm::vec3(200, 100, 0), glm::vec2(50, 50), glm::vec4(0.609f, 0.115f, 0.436f, 1), *m_Shader);
	}

	TestRenderer2D::~TestRenderer2D()
	{
		delete m_Shader;
		delete sprite;
		delete sprite2;
	}

	void TestRenderer2D::OnUpdate(float deltaTime)
	{
	}

	void TestRenderer2D::OnRender()
	{
		rxogl::SimpleRenderer2D renderer;
		renderer.Submit(sprite);
		renderer.Submit(sprite2);
		renderer.Flush();
		//GLCall(glClearColor(m_Color[0], m_Color[1], m_Color[2], m_Color[3]));
		//GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void TestRenderer2D::OnImguiRender()
	{

	}
}