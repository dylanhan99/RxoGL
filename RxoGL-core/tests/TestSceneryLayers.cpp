#include "TestSceneryLayers.h"
#include "../vendor/imgui/imgui.h"
#include "../graphics/renderables/Label.h"

namespace tests
{
	TestSceneryLayers::TestSceneryLayers()
	{

	}

	TestSceneryLayers::~TestSceneryLayers()
	{
		// deleting shaders and renderables is handled in layer destructor already
	}

	void TestSceneryLayers::OnUpdate(float deltaTime)
	{
	}

	void TestSceneryLayers::OnRender()
	{
		glm::mat4 proj = glm::ortho(0.f, 960.f, 0.f, 540.f, -1.0f, 1.0f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

		// m_TileLayer
		{
			//m_Shader1->Bind();
			//glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translation);

			//glm::mat4 mvp = proj * view * model; // This should be handled in Layer. See comment in layer.cpp
			//m_Shader1->SetUniformMat4f("u_MVP", mvp);
			//m_TileLayer->Render();
		}
	}

	void TestSceneryLayers::OnImguiRender()
	{

	}
}