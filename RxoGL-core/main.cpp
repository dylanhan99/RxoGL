//#include "graphics/window.h"
//#include "utils/fileutils.h"
//#include "graphics/shader.h"

//#include "vendor/imgui/imgui.h"
//#include "vendor/imgui/imgui_impl_glfw.h"
//#include "vendor/imgui/imgui_impl_opengl3.h"

//#include "tests/TestClearColor.h"
//#include "tests/TestTexture2D.h"
//#include "tests/TestTexture3D.h"
//#include "tests/TestSimpleRenderer2D.h"
//#include "tests/TestSimpleBatchRenderer2D.h"
#include "tests/TestMultipleLayer.h"
#include "tests/TestGroups.h"
#include "tests/TestTextRender.h"

#include "Application.h"

int main()
{
	rxogl::Application* application = rxogl::Application::GetInstance();
	application->SetWindow("rxogl", 960, 540);
	const Window& window = application->GetWindow();

	//tests::Test* currentTest = nullptr;
	//tests::TestMenu* testMenu = new tests::TestMenu(currentTest);
	////testMenu->RegisterTest<tests::TestClearColor>("Clear Color");
	//testMenu->RegisterTest<tests::TestTexture2D>("2D Texture");
	//testMenu->RegisterTest<tests::TestTexture3D>("3D Texture");
	//
	////tests::TestTexture2D* test = new tests::TestTexture2D();
	//tests::TestSimpleRenderer2D* test = new tests::TestSimpleRenderer2D();
	//tests::TestSimpleBatchRenderer2D* test = new tests::TestSimpleBatchRenderer2D();
	//tests::TestMultipleLayer* test = new tests::TestMultipleLayer();
	//tests::TestGroups* test = new tests::TestGroups();
	////tests::TestTextRender* test = new tests::TestTextRender();
	//
	//currentTest = test;

	float m_LastFrameTime = 0.f;
	while (!window.closed())
	{
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (application)
		{
			float time = (float)glfwGetTime(); // In seconds
			rxogl::DeltaTime deltaTime = time - m_LastFrameTime;
			m_LastFrameTime = time;

			application->OnUpdate((float)deltaTime);
			application->OnRender();
			application->OnImguiRender();
		}
		window.update();
	}
	return 0;
}