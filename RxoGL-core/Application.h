#pragma once

#include "rxogl.h"
#include "Scene.h"

namespace rxogl
{
	class Application
	{
	private: 
		static Application* m_Instance; // Singleton
		Window m_Window;

		scenes::Scene*		m_CurrentScene = nullptr;
		scenes::SceneMenu*	m_SceneMenu;
		
		void Init();
	protected:
		Application();
	public:
		Application(const char* title, int width, int height);
		~Application();

		template<typename T>
		void RegisterScene(const std::string& name)
		{
			m_SceneMenu.RegisterScene<T>(name);
		}
		void SetWindow(const char* title, int width, int height);

		void OnUpdate(float deltatime);
		void OnRender();
		void OnImguiRender(); // Debug mode

		static Application* GetInstance()
		{
			if (m_Instance == NULL)
				m_Instance = new Application();

			return m_Instance;
		}
		inline const Window& GetWindow() const { return m_Window; }
	};
}