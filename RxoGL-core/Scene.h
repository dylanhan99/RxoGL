#pragma once
#include <functional>
#include <string>
#include <vector>
#include <iostream>

#include "graphics/layers/Layer.h"

namespace rxogl { namespace scenes {
	class Scene
	{
	protected:
		std::vector<Layer*> m_Layers;
	public:
		Scene() {}
		virtual ~Scene() 
		{
			for (auto* layer : m_Layers)
				delete layer;
		}

		virtual void OnUpdate(float deltatime) {}
		virtual void OnRender() 
		{
			for (auto* layer : m_Layers)
				layer->Render();
		}
		virtual void OnImguiRender() {}
	};

	class SceneMenu : public Scene
	{
	private: 
		Scene** m_CurrentScene;
		std::vector<std::pair<std::string, std::function<Scene* ()>>> m_Scenes;
	public:
		SceneMenu() {}
		SceneMenu(Scene* currentScenePointer);
		~SceneMenu();

		void OnImguiRender() override;

		template<typename T>
		void RegisterScene(const std::string& name)
		{
			std::cout << "Registering test " << name << std::endl;
			m_Scenes.push_back(std::make_pair(name, []() { return new T(); }));
		}
	};
} }