#pragma once

#include "Event.h"

#include "graphics/window.h"
#include "Scene.h"

#include "graphics/textures/TextureManager.h"
#include "physics/PhysicsManager.h"

namespace rxogl
{
	class Application
	{
	private: 
		static Application* m_Instance; // Singleton
		std::unique_ptr<Window> m_Window;

		std::unique_ptr<scenes::SceneMenu> m_SceneMenu;
		mutable scenes::Scene* m_CurrentScene;
		std::unordered_map<std::string, scenes::Scene*> m_Scenes;
		FontManager m_FontManager;
		TextureManager m_TextureManager;
		CollisionManager m_CollisionManager;
		PhysicsManager m_PhysicsManager;

		void Init();
	protected:
		Application();
	public:
		Application(std::string title, int& width, int& height);
		~Application();

		static void DeleteInstance()
		{
			if (m_Instance)
			{
				delete m_Instance;
				m_Instance = NULL;
			}
		}

		template<typename T>
		void RegisterScene(const std::string& name)
		{
			m_Scenes[name] = new T();
		}

		void SetWindow(std::string title, int width, int height);

		void OnUpdate(float deltatime);
		void OnRender();
		void OnImguiRender(); // Debug mode

		static Application* GetInstance()
		{
			if (m_Instance == NULL)
				m_Instance = new Application();

			return m_Instance;
		}
		inline const Window&		 GetWindow()		const { return *m_Window; }
		inline const scenes::Scene&	 GetCurrentScene()	const { return *m_CurrentScene; }
		inline FontManager&	 GetFontManager() { return m_FontManager; }
		inline TextureManager&	 GetTextureManager() { return m_TextureManager; }
		inline CollisionManager& GetCollisionManager() { return m_CollisionManager; }
		inline PhysicsManager&	 GetPhysicsManager() { return m_PhysicsManager; }
		inline const void SetCurrentScene(std::string sceneName) const { m_CurrentScene = m_Scenes.at(sceneName); }
		//bool OnWindowResize(WindowResizeEvent& e)
	};
}