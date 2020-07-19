#include <iostream>
#include "rxogl.h"
#include "Scenes/MainScene.h"

int main()
{
	rxogl::Application* application = rxogl::Application::GetInstance();
	//application->SetWindow("rxogl", 960, 540);
	const Window& window = application->GetWindow();

	application->RegisterScene<Game::Scenes::MainScene>("MainScene");
	application->SetCurrentScene("MainScene");

	float m_LastFrameTime = 0.f;
	while (!window.Closed())
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
			if (!window.IsMinimized())
				application->OnRender();
			application->OnImguiRender();
		}
		window.Update();
	}
	application->DeleteInstance();
	Events::EventDispatcher::DeleteInstance();
	return 0;
}