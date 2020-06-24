#include "graphics/window.h"
//#include "utils/fileutils.h"
#include "graphics/shader.h"

#include "graphics/buffers/VertexArray.h"
#include "graphics/buffers/Buffer.h"
#include "graphics/renderers/Renderer2D.h"
#include "graphics/Texture.h"

//#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"

//#include "tests/TestClearColor.h"
//#include "tests/TestTexture2D.h"
//#include "tests/TestTexture3D.h"
//#include "tests/TestSimpleRenderer2D.h"
//#include "tests/TestSimpleBatchRenderer2D.h"
#include "tests/TestMultipleLayer.h"
#include "tests/TestGroups.h"
#include "tests/TestTextRender.h"

int main()
{
	Window window("rxogl", 960, 540);
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	std::cout << glGetString(GL_VERSION) << std::endl;

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	//rxogl::SimpleRenderer2D renderer;

	// Setting up imgui
	{
		// GL 3.0 + GLSL 130
		const char* glsl_version = "#version 130";
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
		//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(window.GetWindow(), true);
		ImGui_ImplOpenGL3_Init(glsl_version);
		//io.Fonts->AddFontDefault();
		//ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
		//IM_ASSERT(font != NULL);
	}

	tests::Test* currentTest = nullptr;
	tests::TestMenu* testMenu = new tests::TestMenu(currentTest);
	//testMenu->RegisterTest<tests::TestClearColor>("Clear Color");
	//testMenu->RegisterTest<tests::TestTexture2D>("2D Texture");
	//testMenu->RegisterTest<tests::TestTexture3D>("3D Texture");

	//tests::TestTexture2D* test = new tests::TestTexture2D();
	//tests::TestSimpleRenderer2D* test = new tests::TestSimpleRenderer2D();
	//tests::TestSimpleBatchRenderer2D* test = new tests::TestSimpleBatchRenderer2D();
	//tests::TestMultipleLayer* test = new tests::TestMultipleLayer();
	//tests::TestGroups* test = new tests::TestGroups();
	tests::TestTextRender* test = new tests::TestTextRender();

	currentTest = test;

	while (!window.closed())
	{
		//renderer.Clear();
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (currentTest)
		{
			currentTest->OnUpdate(0.0f);
			currentTest->OnRender();
			ImGui::Begin("Test");
			if (currentTest != testMenu && ImGui::Button("<-"))
			{
				delete currentTest;
				currentTest = testMenu;
			}
			currentTest->OnImguiRender();
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		window.update();
	}
	if (currentTest != testMenu)
		delete testMenu;
	delete currentTest;
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	return 0;
}