#include "Application.h"

#include "SceneTest.h"

namespace rxogl
{
	Application* Application::m_Instance = NULL;

	Application::Application()
	{
		Init();
	}

	Application::Application(const char* title, int width, int height)
		: m_Window(new Window(title, &width, &height))
	{
		Init();
	}

	Application::~Application()
	{
		delete m_SceneMenu;

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		delete m_Window;
	}

	void Application::Init()
	{
		SetWindow("rxogl", 960, 540);
		GLCall(glClearColor(0.2f, 0.3f, 0.8f, 1.0f));

		std::cout << glGetString(GL_VERSION) << std::endl;

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

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
			ImGui_ImplGlfw_InitForOpenGL(m_Window->GetWindow(), true);
			ImGui_ImplOpenGL3_Init(glsl_version);
			//io.Fonts->AddFontDefault();
			//ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
			//IM_ASSERT(font != NULL);
		}

		m_SceneMenu = new scenes::SceneMenu(m_CurrentScene);
		//m_SceneMenu->RegisterScene<scenes::SceneMainMenu>("Main Menu");
		//tests::TestGroups* test = new tests::TestGroups();
		//tests::TestTextRender* test = new tests::TestTextRender();
		//currentTest = test;

		m_SceneMenu->RegisterScene<scenes::SceneTest>("Test");
		scenes::SceneTest* test = new scenes::SceneTest();
		m_CurrentScene = test;
	}

	void Application::SetWindow(const char* title, int width, int height)
	{
		m_Window = new Window(title, &width, &height);
	}

	void Application::OnUpdate(float deltatime)
	{
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		m_CurrentScene->OnUpdate(deltatime);
	}

	void Application::OnRender()
	{
		m_CurrentScene->OnRender();
	}

	void Application::OnImguiRender()
	{
		ImGui::Begin("Scenes");
		if (m_CurrentScene != m_SceneMenu && ImGui::Button("<-"))
		{
			delete m_CurrentScene;
			m_CurrentScene = m_SceneMenu;
		}
		m_CurrentScene->OnImguiRender();

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}