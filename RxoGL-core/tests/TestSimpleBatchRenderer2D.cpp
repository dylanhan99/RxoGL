#include "TestSimpleBatchRenderer2D.h"
#include "../vendor/imgui/imgui.h"

namespace tests
{
	TestSimpleBatchRenderer2D::TestSimpleBatchRenderer2D()
	{
		m_Shader = new Shader("res/shaders/basic.vert", "res/shaders/basic.frag");
		int count = 0;
		float size = 30;
		float width = size - 5;
		for (float y = 0; y < 540; y += size)
		{
			for (float x = 0; x < 960; x += size)
			{
				sprites.push_back(new rxogl::Sprite(glm::vec3(x, y, 0), 
													glm::vec2(width, width),
													glm::vec4(rand() % 1000 / 1000.f, rand() % 1000 / 1000.f, rand() % 1000 / 1000.f, 1)));
				count++;
			}
		}
		std::cout << count << std::endl;
		m_Shader->Bind();
	}

	TestSimpleBatchRenderer2D::~TestSimpleBatchRenderer2D()
	{
		delete m_Shader;
		for (rxogl::Renderable2D* s : sprites)
		{
			delete s;
		}
	}

	void TestSimpleBatchRenderer2D::OnUpdate(float deltaTime)
	{

	}

	void TestSimpleBatchRenderer2D::OnRender()
	{
		glm::mat4 proj = glm::ortho(0.f, 960.f, 0.f, 540.f, -1.0f, 1.0f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		glm::mat4 mvp = proj * view * model;
		m_Shader->SetUniformMat4f("u_MVP", mvp);

		rxogl::BatchRenderer2D renderer;
		renderer.Begin();
		for (int i = 0; i < sprites.size(); i++)
		{
			renderer.Submit(sprites[i]);
		}
		renderer.End();
		renderer.Flush();
	}

	void TestSimpleBatchRenderer2D::OnImguiRender()
	{

	}
}