#pragma once
#include <functional>
#include <string>
#include <vector>
#include <iostream>

#include "graphics/layers/Layer.h"
#include "graphics/fonts/FontManager.h"

namespace rxogl { namespace scenes {
	class Scene
	{
	protected:
		std::vector<std::shared_ptr<Layer>> m_Layers;
	public:
		Scene() {}
		virtual ~Scene() {}

		virtual void OnUpdate(float deltatime) 
		{
			for (auto& layer : m_Layers)
				layer->Update(deltatime);
		}
		virtual void OnRender() 
		{
			for (auto& layer : m_Layers)
				layer->Render();
		}
		virtual void OnImguiRender() {}

		void AddLayer(Layer* newLayer) { m_Layers.push_back(std::make_shared<Layer>(*newLayer)); }
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