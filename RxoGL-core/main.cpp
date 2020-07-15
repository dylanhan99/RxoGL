#include "Application.h"


#include "Event.h"

void testCallback(int a) {
	std::cout << "AAAAAA " << a << std::endl;
}

void testCallback2() {
	std::cout << "ZZZZZZ " << std::endl;
}

void testCallback3() {
	std::cout << "PPPPPP " << std::endl;
}

void testCallback4(float a, float b) {
	std::cout << a << ", " << b << std::endl;
}

int main()
{
	//Events::EventDispatcher* eventDisp = Events::EventDispatcher::GetInstance();
	//eventDisp->RegisterEvent(new Events::Event<int>("TestEvent", &testCallback));
	//eventDisp->RegisterEvent(new Events::Event<>("TestEvent", &testCallback2));
	//eventDisp->RegisterEvent(new Events::Event<>("TestEvent", &testCallback3));
	//eventDisp->DispatchEvent("TestEvent", 20);	// Calls callback
	//eventDisp->DispatchEvent("TestEvent");		// Calls callback2
	//Events::EventDispatcher::GetInstance()->RegisterEvent(new Events::Event<float, float>(rxogl::constants::RX_EVENT_WINDOWRESIZE, &testCallback4));
	//Events::EventDispatcher::GetInstance()->DispatchEvent(rxogl::constants::RX_EVENT_WINDOWRESIZE, 20.12f, 21.32f);	// Calls callback
	//return 0;


	rxogl::Application* application = rxogl::Application::GetInstance();
	//application->SetWindow("rxogl", 960, 540);
	const Window& window = application->GetWindow();

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
			if(!window.IsMinimized())
				application->OnRender();	
			application->OnImguiRender();
		}
		window.Update();
	}
	return 0;
}