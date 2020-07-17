#pragma once

#include "Event.h"

#include "rxogl.h"
#include "Scene.h"

namespace rxogl
{
	class Application
	{
	private: 
		static Application* m_Instance; // Singleton
		Window* m_Window;

		scenes::SceneMenu*	m_SceneMenu;
		mutable scenes::Scene*		m_CurrentScene;
		std::unordered_map<std::string, scenes::Scene*> m_Scenes;
		
		void Init();
	protected:
		Application();
	public:
		Application(const char* title, int width, int height);
		~Application();

		//template<typename T>
		//void RegisterScene(const std::string& name)
		//{
		//	m_SceneMenu.RegisterScene<T>(name);
		//}

		template<typename T>
		void RegisterScene(const std::string& name)
		{
			m_Scenes[name] = new T();
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
		inline const Window& GetWindow() const { return *m_Window; }
		inline const scenes::Scene& GetCurrentScene() const { return *m_CurrentScene; }
		inline const void SetCurrentScene(std::string sceneName) const { m_CurrentScene = m_Scenes.at(sceneName); }
		//bool OnWindowResize(WindowResizeEvent& e)
	};
}